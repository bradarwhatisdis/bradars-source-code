#!/bin/bash

# Konfigurasi
LIBRARY="app/src/main/libs/arm64-v8a/library.so"
INJECTION_PATH="inject-app/lib/arm64-v8a/"
APP_PATH="inject-app"
OUTPUT_DIR="output"
KEYSTORE="tmp.jks"

# 1. Cek dependencies (biar tidak install ulang terus)
for tool in zipalign 7z apksigner; do
    if ! command -v $tool &> /dev/null; then
        echo "📦 Memasang $tool..."
        sudo apt install zipalign p7z-full apksigner -y
    fi
done

# 2. Validasi file sumber
if [ ! -f "$LIBRARY" ]; then
    echo "❌ ERROR: File $LIBRARY tidak ditemukan!"
    exit 1
fi

# 3. Validasi & Siapkan folder tujuan
# Gunakan -d untuk cek direktori
if [ ! -d "$INJECTION_PATH" ]; then
    echo "📂 Folder tujuan tidak ada. Membuat folder: $INJECTION_PATH"
    mkdir -p "$INJECTION_PATH"
fi

# 4. Proses Injection
echo "🚀 -- Injecting library.so ... --"
cp "$LIBRARY" "$INJECTION_PATH"
sleep 0.5

# Siapkan folder output
mkdir -p "$OUTPUT_DIR"

# 5. Repack
echo "📦 -- Repacking APK ... --"
# Hapus file lama jika ada agar tidak tertumpuk di dalam zip
rm -f "$OUTPUT_DIR/injected-not-aligned.apk"
7z a -tzip "$OUTPUT_DIR/injected-not-aligned.apk" "./$APP_PATH/*" -mx0 # mx0 = fast compression

# 6. Zipalign
echo "⚖️ -- Aligning APK ... --"
zipalign -v 4 "$OUTPUT_DIR/injected-not-aligned.apk" "$OUTPUT_DIR/injected-aligned.apk"

# 7. Signing
echo "✍️ -- Signing APK ... --"
# Catatan: Jika keystore punya password, tambahkan: --ks-pass pass:PASSWORD_KAMU
apksigner sign --ks-pass pass:reyzz011 --ks "$KEYSTORE" --out "$OUTPUT_DIR/injected-final.apk" "$OUTPUT_DIR/injected-aligned.apk"

echo "✅ -- DONE! File tersimpan di $OUTPUT_DIR/injected-final.apk --"