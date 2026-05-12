#pragma once

#include <Vector/Vectors.h>
#include <imgui/imgui.h>
#include <map>
#include <string>

#include "icons/icons.h"

using namespace ImGui;
using namespace std;

#include "include/includes.h"

#include "game.h"
#include "game/Ruleset.h"
#include "imgui/inc/8bp.h"
#include "mod/keylogin.h"
#include "oxorany/oxorany.h"

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#include <sys/system_properties.h>
#include <ctime>

// Translation System
enum class Language { ENGLISH, INDONESIAN, SPANISH, PORTUGUESE, TURKISH, VIETNAMESE };
static Language g_currentLanguage = Language::ENGLISH;

// Simple translation map - in practice, this would be more comprehensive
static const char* T(const char* key) {
    static map<Language, map<string, string>> translations = {
        { Language::ENGLISH, {
            {"draw_settings", "Draw Settings"},
            {"auto_play", "Auto Play"},
            {"auto_queue", "Auto Queue"},
            {"user", "User"},
            {"draw_lines", "Draw Lines"},
            {"draw_pockets", "Draw Pockets"},
            {"line_thickness", "Line Thickness"},
            {"fix_menu_size", "Fix Menu Size"},
            {"save_config", "Save Config"},

            {"device", "Device"},
            {"manufacturer", "Manufacturer:"},
            {"model", "Model:"},
            {"abi", "ABI:"},
            {"android", "Android:"},
            {"bradar_s_cheat", "Bradar's Cheat"},
            {"expire", "Expire:"},
            {"owner", "Owner : @profambatukam"},
            {"beware_scammers", "Beware of Scammers. This is a FREE BETA version, if you bought this version it means you got scammed."},
            {"your_will_read", "Your will read"},
            {"copy_license_key", "Copy your license key and tap login"},
            {"authenticating", "Authenticating..."},
            {"login", "Login"},
            {"mod_expired", "MOD EXPIRED"},
            {"beta_version_expired", "Beta Version Expired. Update on our Telegram Your Id"},
            {"calculating", "CALCULATING..."},
            {"close_menu", "Close Menu"},
            // Theme names
            {"theme_default", "Default"},
            {"theme_neon_red", "Neon Red"},
            {"theme_deep_ocean", "Deep Ocean"},
            {"theme_midnight_purple", "Midnight Purple"},
            {"theme_gold_edition", "Gold Edition"},
            // Language names
            {"language_english", "English"},
            {"language_indonesian", "Indonesian"},
            {"language_spanish", "Spanish"},
            {"language_portuguese", "Portuguese"},
            {"language_turkish", "Turkish"},
            {"language_vietnamese", "Vietnamese"},
            // Theme and language labels
            {"theme", "Theme"},
            {"language", "Language"}
        }},
        { Language::INDONESIAN, {
            {"draw_settings", "Pengaturan Gambar"},
            {"auto_play", "Main Otomatis"},
            {"auto_queue", "Antrian Otomatis"},
            {"user", "Pengguna"},
            {"draw_lines", "Gambar Garis"},
            {"draw_pockets", "Gambar Lubang"},
            {"line_thickness", "Ketebalan Garis"},
            {"fix_menu_size", "Ukuran Menu Tetap"},
            {"save_config", "Simpan Konfigurasi"},

            {"mode", "Mode"},
            {"bet_percent", "Persentase Taruhan"},
            {"select_table", "Pilih Meja"},
            {"last_selected", "Terakhir Dipilih"},
            {"smart", "Pintar"},
            {"fix_table", "Meja Tetap"},
            {"you_will_be_auto_queued", "Anda akan otomatis diantrekan ke"},
            {"the_last_game_mode", "mode permainan terakhir yang Anda mainkan"},
            {"device", "Perangkat"},
            {"manufacturer", "Produsen:"},
            {"model", "Model:"},
            {"abi", "ABI:"},
            {"android", "Android:"},
            {"bradar_s_cheat", "Trik Bradar"},
            {"expire", "Kadaluarsa:"},
            {"owner", "Pemilik : @profambatukam"},
            {"beware_scammers", "Waspadai Penipu. Ini adalah versi BETA GRATIS, jika Anda membeli versi ini berarti Anda telah dicurangi."},
            {"your_will_read", "Anda akan membaca"},
            {"copy_license_key", "Salin lisensi kunci dan ketuk login"},
            {"authenticating", "Sedang Mengautentikasi..."},
            {"login", "Masuk"},
            {"mod_expired", "MOD KADALUARSA"},
            {"beta_version_expired", "Versi BETA Kadaluarsa. Perbarui di Telegram Kami Id Anda"},
            {"calculating", "SEDANG MENGHITUNG..."},
            {"close_menu", "Tutup Menu"},
            // Theme names
            {"theme_default", "Default"},
            {"theme_neon_red", "Merah Neon"},
            {"theme_deep_ocean", "Lautan Dalam"},
            {"theme_midnight_purple", "Ungu Tengah Malam"},
            {"theme_gold_edition", "Edisi Emas"},
            // Language names
            {"language_english", "Inggris"},
            {"language_indonesian", "Indonesia"},
            {"language_spanish", "Spanyol"},
            {"language_portuguese", "Portugis"},
            {"language_turkish", "Turki"},
            {"language_vietnamese", "Vietnam"},
            // Theme and language labels
            {"theme", "Tema"},
            {"language", "Bahasa"}
        }}
        // Other languages would follow similar pattern
    };

    auto langIt = translations.find(g_currentLanguage);
    if (langIt != translations.end()) {
        auto keyIt = langIt->second.find(key);
        if (keyIt != langIt->second.end()) {
            return keyIt->second.c_str();
        }
    }
    // Fallback to English
    auto engIt = translations.find(Language::ENGLISH);
    if (engIt != translations.end()) {
        auto keyIt = engIt->second.find(key);
        if (keyIt != engIt->second.end()) {
            return keyIt->second.c_str();
        }
    }
    return key; // Last resort
}

// Theme System
struct Theme {
    ImVec4 primary;
    ImVec4 secondary;
    ImVec4 background;
    ImVec4 text;
    ImVec4 accent;
};

// Predefined themes
static Theme g_themes[] = {
    // Default (matching original)
    { ImVec4(0.90f, 0.20f, 0.35f, 1.0f), ImVec4(0.15f, 0.15f, 0.20f, 1.0f), ImVec4(0.08f, 0.08f, 0.10f, 1.0f), ImVec4(0.90f, 0.90f, 0.95f, 1.0f), ImVec4(0.90f, 0.20f, 0.35f, 1.0f) },
    // Neon Red
    { ImVec4(1.0f, 0.0f, 0.5f, 1.0f), ImVec4(0.2f, 0.0f, 0.3f, 1.0f), ImVec4(0.1f, 0.1f, 0.15f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 0.0f, 0.5f, 1.0f) },
    // Deep Ocean
    { ImVec4(0.0f, 0.5f, 1.0f, 1.0f), ImVec4(0.0f, 0.2f, 0.4f, 1.0f), ImVec4(0.05f, 0.05f, 0.1f, 1.0f), ImVec4(0.8f, 0.8f, 0.9f, 1.0f), ImVec4(0.0f, 0.5f, 1.0f, 1.0f) },
    // Midnight Purple
    { ImVec4(0.6f, 0.0f, 0.8f, 1.0f), ImVec4(0.2f, 0.0f, 0.3f, 1.0f), ImVec4(0.05f, 0.05f, 0.1f, 1.0f), ImVec4(0.9f, 0.9f, 1.0f, 1.0f), ImVec4(0.6f, 0.0f, 0.8f, 1.0f) },
    // Gold Edition
    { ImVec4(1.0f, 0.84f, 0.0f, 1.0f), ImVec4(0.3f, 0.25f, 0.0f, 1.0f), ImVec4(0.1f, 0.1f, 0.15f, 1.0f), ImVec4(0.9f, 0.9f, 0.9f, 1.0f), ImVec4(1.0f, 0.84f, 0.0f, 1.0f) }
};

static int g_currentTheme = 0; // Index into g_themes

// Function to apply theme to ImGui
static void ApplyTheme() {
    if (g_currentTheme < 0 || g_currentTheme >= IM_ARRAYSIZE(g_themes)) return;
    Theme& theme = g_themes[g_currentTheme];
    
    ImGuiStyle& style = ImGui::GetStyle();
    // Window
    style.Colors[ImGuiCol_WindowBg] = theme.background;
    style.Colors[ImGuiCol_Border] = theme.secondary;
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // Text
    style.Colors[ImGuiCol_Text] = theme.text;
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(theme.text.x * 0.5f, theme.text.y * 0.5f, theme.text.z * 0.5f, theme.text.w * 0.5f);
    // Frames
    style.Colors[ImGuiCol_FrameBg] = theme.secondary;
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(theme.secondary.x * 1.1f, theme.secondary.y * 1.1f, theme.secondary.z * 1.1f, theme.secondary.w);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(theme.secondary.x * 1.2f, theme.secondary.y * 1.2f, theme.secondary.z * 1.2f, theme.secondary.w);
    // Buttons
    style.Colors[ImGuiCol_Button] = theme.secondary;
    style.Colors[ImGuiCol_ButtonHovered] = theme.primary;
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(theme.primary.x * 0.8f, theme.primary.y * 0.8f, theme.primary.z * 0.8f, theme.primary.w);
    // Headers
    style.Colors[ImGuiCol_Header] = theme.secondary;
    style.Colors[ImGuiCol_HeaderHovered] = theme.primary;
    style.Colors[ImGuiCol_HeaderActive] = theme.primary;
    // Sliders
    style.Colors[ImGuiCol_SliderGrab] = theme.primary;
    style.Colors[ImGuiCol_SliderGrabActive] = theme.primary;
    // Title
    style.Colors[ImGuiCol_TitleBg] = theme.secondary;
    style.Colors[ImGuiCol_TitleBgActive] = theme.primary;
    style.Colors[ImGuiCol_TitleBgCollapsed] = theme.secondary;
    // Popups
    style.Colors[ImGuiCol_PopupBg] = theme.background;
}

struct MenuState {
    bool isOpen = false;
    int currentTab = 0;
    float sidebarWidth = 0.0f;
    float animProgress = 0.0f;
    float menuAlpha = 0.0f;
    float menuScale = 0.9f;
    ImVec4 accentColor = ImVec4(0.90f, 0.20f, 0.35f, 1.0f);
    ImVec4 secondaryColor = ImVec4(0.15f, 0.15f, 0.20f, 1.0f);
    bool isInitialized = false;
};
static MenuState g_menu;

INLINE float GetResponsiveWidth(ImGuiIO& io) {
    float screenW = io.DisplaySize.x;
    if (screenW <= 720.0f) return 320.0f; // Reduced for better landscape feel
    if (screenW <= 1080.0f) return 380.0f;
    return 440.0f;
}

INLINE float GetResponsiveHeight(ImGuiIO& io) {
    float screenH = io.DisplaySize.y;
    if (screenH <= 720.0f) return 400.0f;
    if (screenH <= 1080.0f) return 460.0f;
    return 520.0f;
}

INLINE float GetResponsiveFontScale(ImGuiIO& io) {
    float screenW = io.DisplaySize.x;
    if (screenW <= 720.0f) return 0.9f;
    if (screenW <= 1080.0f) return 0.95f;
    return 1.0f;
}

// Obfuscated expiry date: 13.04.2026 00:00:00 UTC
static const int64_t EXPIRY_TS = O(1780099200LL);

static bool DEBUG_BYPASS_LOGIN = false;

static float EaseOutBack(float x) {
    const float c1 = 1.70158f;
    const float c3 = c1 + 1.0f;
    return 1.0f + c3 * powf(x - 1.0f, 3.0f) + c1 * powf(x - 1.0f, 2.0f);
}

static float EaseOutQuart(float x) {
    return 1.0f - powf(1.0f - x, 4.0f);
}

static void DrawGradientRect(ImDrawList* dl, ImVec2 p1, ImVec2 p2, ImU32 col1, ImU32 col2, bool horizontal = true) {
    if (horizontal) {
        dl->AddRectFilledMultiColor(p1, p2, col1, col2, col2, col1);
    } else {
        dl->AddRectFilledMultiColor(p1, p2, col1, col1, col2, col2);
    }
}

// Modernized SidebarButton with better touch targets and animation
static bool SidebarButton(const char* label, GLuint iconTex, bool selected, float width, ImVec2 screenSize) {
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems) return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);

    float scaleFactor = GetResponsiveFontScale(g.IO);
    float iconSize   = 40.0f * scaleFactor;
    float vPad       = 10.0f * scaleFactor;
    float btnH       = vPad * 2.0f + iconSize + g.FontSize * scaleFactor;

    ImVec2 pos  = window->DC.CursorPos;
    ImVec2 size = ImVec2(width, btnH);

    const ImRect bb(pos, pos + size);
    ItemSize(size, style.FramePadding.y);
    if (!ItemAdd(bb, id)) return false;

    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held);

    ImDrawList* dl = window->DrawList;

    // Get colors from theme via g_menu (which we'll update to use theme)
    ImVec4 accentCol = g_menu.accentColor;
    ImVec4 bgCol = selected 
        ? ImVec4(accentCol.x * 0.2f, accentCol.y * 0.2f, accentCol.z * 0.2f, 0.6f)
        : ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

    // Background
    if (hovered || selected) {
        ImU32 bgAlpha = selected ? 150 : 80;
        dl->AddRectFilled(bb.Min, bb.Max, IM_COL32(
            (int)(bgCol.x * 255), 
            (int)(bgCol.y * 255), 
            (int)(bgCol.z * 255), 
            bgAlpha
        ), 16.0f * scaleFactor);
    }

    // Icon background (when selected)
    if (selected) {
        float iconBgSize = iconSize * 1.2f;
        ImVec2 iconCenter = ImVec2(
            bb.Min.x + width * 0.5f,
            bb.Min.y + vPad + iconSize * 0.5f
        );
        dl->AddRectFilled(
            ImVec2(iconCenter.x - iconBgSize * 0.5f, iconCenter.y - iconBgSize * 0.5f),
            ImVec2(iconCenter.x + iconBgSize * 0.5f, iconCenter.y + iconBgSize * 0.5f),
            IM_COL32((int)(accentCol.x*255), (int)(accentCol.y*255), (int)(accentCol.z*255), 200), 
            12.0f * scaleFactor
        );
    }

    // Icon
    if (iconTex) {
        float iconDrawSize = iconSize * 0.9f;
        ImVec2 iconCenter = ImVec2(
            bb.Min.x + width * 0.5f,
            bb.Min.y + vPad + iconSize * 0.5f
        );
        ImVec2 iconMin = ImVec2(iconCenter.x - iconDrawSize * 0.5f, iconCenter.y - iconDrawSize * 0.5f);
        ImVec2 iconMax = ImVec2(iconCenter.x + iconDrawSize * 0.5f, iconCenter.y + iconDrawSize * 0.5f);
        ImU32 tint = selected ? IM_COL32(255, 255, 255, 255) : IM_COL32(220, 220, 230, 255);
        dl->AddImage((void*)(intptr_t)iconTex, iconMin, iconMax, ImVec2(0,0), ImVec2(1,1), tint);
    }

    // Label
    ImVec2 labelSize = CalcTextSize(label);
    ImVec2 textPos   = ImVec2(
        bb.Min.x + (width - labelSize.x) * 0.5f,
        bb.Min.y + vPad * 2.0f + iconSize
    );
    ImU32 textCol = selected 
        ? IM_COL32(255, 255, 255, 255) 
        : (hovered ? IM_COL32(220, 220, 230, 255) : IM_COL32(160, 160, 170, 255));
    dl->AddText(textPos, textCol, label);

    return pressed;
}

// Modernized ToggleSwitch with theme colors and better touch targets
static bool ToggleSwitch(const char* label, bool* v, float scaleFactor = 1.0f) {
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems) return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);

    // Use responsive scale factor
    scaleFactor = scaleFactor > 0.0f ? scaleFactor : GetResponsiveFontScale(g.IO);
    float height = 36.0f * scaleFactor;
    float width = 56.0f * scaleFactor;
    float radius = height * 0.5f;

    ImVec2 textSize = CalcTextSize(label);
    ImVec2 pos = window->DC.CursorPos;
    ImVec2 size = ImVec2(GetContentRegionAvail().x, ImMax(height, textSize.y) + style.FramePadding.y * 2 + 8.0f);

    const ImRect bb(pos, pos + size);
    ItemSize(size, style.FramePadding.y);
    if (!ItemAdd(bb, id)) return false;

    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held);
    if (pressed) *v = !*v;

    static std::map<ImGuiID, float> switchAnim;
    float& animT = switchAnim[id];
    float targetT = *v ? 1.0f : 0.0f;
    animT += (targetT - animT) * g.IO.DeltaTime * 12.0f; // Slightly slower animation

    ImDrawList* dl = window->DrawList;
    
    // Use theme colors
    ImVec4 accentCol = g_menu.accentColor;
    
    // Hover effect
    if (hovered) {
        dl->AddRectFilled(bb.Min, bb.Max, IM_COL32(
            (int)(accentCol.x * 30), 
            (int)(accentCol.y * 30), 
            (int)(accentCol.z * 30), 
            60
        ), radius);
    }
    
    // Toggle background
    ImVec2 togglePos = ImVec2(bb.Max.x - width - 12.0f, bb.Min.y + (size.y - height) * 0.5f);
    ImVec2 toggleEnd = ImVec2(togglePos.x + width, togglePos.y + height);
    
    ImVec4 offColor = ImVec4(0.18f, 0.18f, 0.22f, 1.0f);
    ImVec4 onColor = ImVec4(accentCol.x, accentCol.y, accentCol.z, 1.0f);
    ImVec4 bgColorV = ImLerp(offColor, onColor, animT);
    dl->AddRectFilled(togglePos, toggleEnd, ImColor(bgColorV), radius);
    
    // Toggle knob
    float knobX = togglePos.x + radius + (width - height) * animT;
    float knobY = togglePos.y + radius;
    float knobR = radius - 4.0f;
    
    dl->AddCircleFilled(ImVec2(knobX, knobY), knobR + 2.0f, IM_COL32(0, 0, 0, 30));
    dl->AddCircleFilled(ImVec2(knobX, knobY), knobR, IM_COL32(255, 255, 255, 255));

    // Label with better spacing
    dl->AddText(ImVec2(bb.Min.x + 12.0f * scaleFactor, bb.Min.y + (size.y - textSize.y) * 0.5f), 
                IM_COL32(220, 220, 230, 255), label);

    return pressed;
}




static bool IsExpired() {
    return (int64_t)time(nullptr) >= EXPIRY_TS;
}

INLINE void DrawExpired(ImGuiIO& io) {
    float winW = g_menu.sidebarWidth;

    SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    SetNextWindowSize(ImVec2(winW, 0), ImGuiCond_Always);
    PushStyleColor(ImGuiCol_WindowBg, IM_COL32(21, 21, 21, 255));
    PushStyleVar(ImGuiStyleVar_WindowRounding, 20.0f);
    PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(30.0f, 30.0f));
    PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    if (Begin(T("##ExpiredWin"), nullptr,
              ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
              ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings |
              ImGuiWindowFlags_AlwaysAutoResize)) {

        SetWindowFontScale(1.6f);
        ImVec2 titleSz = CalcTextSize(T("MOD EXPIRED"));
        SetCursorPosX((winW - 60.0f - titleSz.x) * 0.5f);
        TextColored(ImVec4(1.0f, 0.1f, 0.1f, 1.0f), "%s", T("MOD EXPIRED"));
        SetWindowFontScale(1.0f);

        Dummy(ImVec2(0, 16));

        PushTextWrapPos(GetCursorPosX() + winW - 60.0f);
        TextColored(ImVec4(0.85f, 0.85f, 0.90f, 1.0f), "%s",
            T("Beta Version Expired. Update on our Telegram Your Id"));
        PopTextWrapPos();

        Dummy(ImVec2(0, 10));
    }
    End();
    PopStyleVar(3);
    PopStyleColor();
}



#include "mod/ButtonClicker.h"


INLINE void DrawESP(ImDrawList* draw) {
    if ((!g_Token.empty() && !g_Auth.empty() && g_Token == g_Auth) || DEBUG_BYPASS_LOGIN) {
        if (!sharedGameManager) return;

        UpdateScreenTable();

        sharedDirector = F(ptr, libmain + O(0x4f06288));
        if (!sharedDirector) return;

        sharedUserInfo = F(ptr, libmain + O(0x4e9feb8));
        if (!sharedUserInfo) return;

        F(bool, sharedUserInfo + 0x340) = true;

        sharedMainManager = F(ptr, libmain + O(0x4dde3e0));
        if (!sharedMainManager) return;

        sharedMenuManager = F(ptr, libmain + O(0x4dfe838));
        if (!sharedMenuManager) return;

        MainStateManager mainStateManager = sharedMainManager.mStateManager;
        if (!mainStateManager) return;
        if (!mainStateManager.isInGame()) {
            // AutoPlay/AutoQueue features removed
            return;
        }

        auto visualCue = sharedGameManager.mVisualCue();

        Ball::Classification myclass = sharedGameManager.getPlayerClassification();

        Table table = sharedGameManager.mTable;
        if (!table) return;

        auto tableProperties = table.mTableProperties();
        if (!tableProperties) return;

        auto& pockets = tableProperties.mPockets();

        if (persistent_bool[O("bESP_DrawPockets")]) {
            for (int i = 0; i < 6; i++) {
                auto screenPos = WorldToScreen(pockets[i]);
                draw->AddCircle(ImVec2(screenPos.x, screenPos.y), 40, WHITE, 0, 3.f);
            }
        }

        GameStateManager gameStateManager = sharedGameManager.mStateManager;
        if (!gameStateManager) return;

        //      AutoPlay::Update();
        //if (persistent_bool[O("bAutoAim")]) AutoAim::AIM();

        auto stateId = gameStateManager.getCurrentStateId();
        if (stateId == 4) gPrediction->determineShotResult(false);
        if (stateId == 6 || stateId == 7 || stateId == 8) return;

        if (persistent_bool[O("bESP_DrawPocketsShotState")]) {
            for (int i = 0; i < 6; i++) {
                if (Prediction::pocketStatus[i]) {
                    auto screenPos = WorldToScreen(pockets[i]);
                    draw->AddCircle(ImVec2(screenPos.x, screenPos.y), 30, GREEN, 0, 5.f);
                }
            }
        }

        if (persistent_bool[O("bESP_DrawPredictionLine")]) {
            for (int i = 0; i < gPrediction->guiData.ballsCount; i++) {
                auto& ball = gPrediction->guiData.balls[i];

                if (ball.initialPosition != ball.predictedPosition) {
                    ImVec2 lastPos{};
                    float lineThick = (float)persistent_int[O("iLineThickness")];
                    if (lineThick < 1.f) lineThick = 1.f;
                    for (int j = 1; j < ball.positions.size(); j++) {
                        auto point = WorldToScreen(ball.positions[j]);
                        if (lastPos.x || lastPos.y) draw->AddLine(lastPos, point, colors[i], lineThick);
                        lastPos = point;
                    }
                }
            }
        }

        if (persistent_bool[O("bESP_DrawPredictionLine")]) {
            for (int i = 0; i < gPrediction->guiData.ballsCount; i++) {
                auto& ball = gPrediction->guiData.balls[i];

                if (ball.initialPosition != ball.predictedPosition) {
                    float circleR = (float)persistent_int[O("iLineThickness")] + 1.f;
                    if (circleR < 2.f) circleR = 2.f;
                    draw->AddCircleFilled(WorldToScreen(ball.initialPosition), circleR, colors[i]);
                    draw->AddCircleFilled(WorldToScreen(ball.predictedPosition), 16, colors[i]);
                }
            }
        }
    }
}

static void DrawSidebar(float sidebarW, ImVec2 screenSize) {
    static GLuint draw_icon_tex = LoadTextureFromMemory(draw_icon_png, draw_icon_png_len);
    static GLuint play_icon_tex = LoadTextureFromMemory(play_icon_png, play_icon_png_len);
    static GLuint q_icon_tex    = LoadTextureFromMemory(q_icon_png,    q_icon_png_len);
    static GLuint user_icon_tex = LoadTextureFromMemory(user_icon_png, user_icon_png_len);

    ImGuiContext& g  = *GImGui;
    ImDrawList*   dl = GetWindowDrawList();
    ImVec2        wp = GetWindowPos();

    float scaleFactor = GetResponsiveFontScale(g.IO);
    float closeSize = 28.0f * scaleFactor;
    float closeBtnW = 50.0f * scaleFactor;
    float tabsW     = sidebarW - closeBtnW;
    float btnW      = tabsW / 4.0f;
    float marginB   = 12.0f * scaleFactor;

    dl->ChannelsSplit(2);
    dl->ChannelsSetCurrent(1);

    BeginGroup();
    SetCursorPos(ImVec2(0.0f, 0.0f));
    if (SidebarButton(T("draw_settings"),  draw_icon_tex, g_menu.currentTab == 0, btnW, screenSize)) g_menu.currentTab = 0;
    SameLine(0, 0);
    if (SidebarButton(T("auto_play"),  play_icon_tex, g_menu.currentTab == 1, btnW, screenSize)) g_menu.currentTab = 1;
    SameLine(0, 0);
    if (SidebarButton(T("auto_queue"), q_icon_tex,    g_menu.currentTab == 2, btnW, screenSize)) g_menu.currentTab = 2;
    SameLine(0, 0);
    if (SidebarButton(T("user"),  user_icon_tex, g_menu.currentTab == 3, btnW, screenSize)) g_menu.currentTab = 3;
    EndGroup();

    float sidebarH = GetItemRectMax().y - wp.y;

    dl->ChannelsSetCurrent(0);
    
    ImVec4 accentCol = g_menu.accentColor;
    dl->AddRectFilled(wp, ImVec2(wp.x + sidebarW, wp.y + sidebarH), IM_COL32(18, 18, 22, 255), 16.0f * scaleFactor);
    
    // Simplified gradient - just a subtle accent at top
    ImVec2 gradientStart(wp.x, wp.y);
    ImVec2 gradientEnd(wp.x + sidebarW, wp.y + sidebarH * 0.1f);
    dl->AddRectFilledMultiColor(
        gradientStart, gradientEnd,
        IM_COL32((int)(accentCol.x*40), (int)(accentCol.y*40), (int)(accentCol.z*40), 180),
        IM_COL32((int)(accentCol.x*20), (int)(accentCol.y*20), (int)(accentCol.z*20), 180),
        IM_COL32((int)(accentCol.x*20), (int)(accentCol.y*20), (int)(accentCol.z*20), 180),
        IM_COL32((int)(accentCol.x*40), (int)(accentCol.y*40), (int)(accentCol.z*40), 180)
    );
    
    dl->ChannelsMerge();

    // Simplified separator
    float sepX       = wp.x + sidebarW - closeBtnW;
    float sepCenterY = wp.y + sidebarH * 0.5f;
    float sepHalfH   = sidebarH * 0.25f;
    dl->AddLine(
        ImVec2(sepX, sepCenterY - sepHalfH),
        ImVec2(sepX, sepCenterY + sepHalfH),
        IM_COL32(70, 70, 85, 100), 1.0f
    );

    // Close button
    float closePosX = (sidebarW - closeBtnW) + (closeBtnW - closeSize) * 0.5f;
    float closePosY = (sidebarH - closeSize) * 0.5f;
    SetCursorPos(ImVec2(closePosX, closePosY));
    {
        ImGuiWindow* win = GetCurrentWindow();
        ImGuiID closeId  = win->GetID(T("##CloseMenu"));
        ImVec2 closePos  = win->DC.CursorPos;
        ImRect closeBb(closePos, closePos + ImVec2(closeSize, closeSize));
        ItemSize(ImVec2(closeSize, closeSize), g.Style.FramePadding.y);
        ItemAdd(closeBb, closeId);
        bool closeHovered = false, closeHeld = false;
        bool closePressed = ButtonBehavior(closeBb, closeId, &closeHovered, &closeHeld);
        if (closePressed) g_menu.isOpen = false;

        float xCX = closeBb.Min.x + closeSize * 0.5f;
        float xCY = closeBb.Min.y + closeSize * 0.5f;
        float xH  = closeSize * 0.3f;
        ImU32 xCol = closeHovered 
            ? IM_COL32(255, 100, 100, 200) 
            : IM_COL32(180, 180, 190, 150);
        dl->AddLine(ImVec2(xCX - xH, xCY - xH), ImVec2(xCX + xH, xCY + xH), xCol, 1.5f);
        dl->AddLine(ImVec2(xCX + xH, xCY - xH), ImVec2(xCX - xH, xCY + xH), xCol, 1.5f);
    }

    SetCursorPos(ImVec2(0.0f, sidebarH));
    Dummy(ImVec2(sidebarW, marginB));
}

// Reads an IL2CPP/Unity NSString (UTF-16 internal buffer at offset 0x14, length at 0x10)
static std::string ReadNSString(ptr str) {
    if (!str) return "null";
    int32_t len = F(int32_t, str + 0x10);
    if (len <= 0 || len > 512) return "?";
    std::string result;
    result.reserve(len);
    for (int32_t i = 0; i < len; i++) {
        uint16_t ch = F(uint16_t, str + 0x14 + i * 2);
        result += (ch > 0 && ch < 128) ? (char)ch : '?';
    }
    return result;
}

// Shared vertical position for DrawToggleButton and DrawFloatingButton (they move together)
static float g_sideBtnsY      = 0.0f;
// Kept for linker compatibility — no longer used for animation
static float g_toggleRotAngle = 0.0f;
// Set true by AutoPlay when in SLOW scan state — shows CALCULATING overlay
static bool  g_autoPlayCalculating = false;

// ── svConfig ──────────────────────────────────────────────────────────────────
static void svConfig_Save() {
    std::string path = O("/data/user/0/") + PACKAGE_NAME + O("/files/svConfig.txt");
    FILE* f = fopen(path.c_str(), O("w"));
    if (!f) return;
    fprintf(f, O("iLineThickness=%d\n"),  persistent_int[O("iLineThickness")]);
    fprintf(f, O("iMenuSizeOffset=%d\n"), persistent_int[O("iMenuSizeOffset")]);
    fclose(f);
}
static void svConfig_Load() {
    std::string path = O("/data/user/0/") + PACKAGE_NAME + O("/files/svConfig.txt");
    FILE* f = fopen(path.c_str(), O("r"));
    if (!f) return;
    char line[64];
    while (fgets(line, sizeof(line), f)) {
        int v = 0;
        if (sscanf(line, O("iLineThickness=%d"),  &v) == 1) { persistent_int[O("iLineThickness")]  = v; continue; }
        if (sscanf(line, O("iMenuSizeOffset=%d"), &v) == 1) { persistent_int[O("iMenuSizeOffset")] = v; }
    }
    fclose(f);
}

// ── CALCULATING overlay (shown during AutoPlay SLOW scan) ─────────────────────
static void DrawCalculating(ImGuiIO& io) {
    float scaleFactor = io.DisplaySize.x <= 720.0f ? 0.7f : (io.DisplaySize.x <= 1080.0f ? 0.85f : 1.0f);
    SetNextWindowPos(ImVec2(Width * 0.5f, Height * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    
    PushStyleColor(ImGuiCol_WindowBg, IM_COL32(18, 18, 22, 255));
    ImVec4 accentCol = g_menu.accentColor;
    PushStyleColor(ImGuiCol_Border, IM_COL32((int)(accentCol.x*255), (int)(accentCol.y*255), (int)(accentCol.z*255), 255));
    PushStyleVar(ImGuiStyleVar_WindowRounding, 14.0f * scaleFactor);
    PushStyleVar(ImGuiStyleVar_WindowBorderSize, 2.0f);

    if (Begin(O("##CalcOverlay"), nullptr,
              ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | 
              ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | 
              ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoInputs)) {
        
        SetWindowFontScale(1.2f * scaleFactor);
        TextColored(ImVec4(accentCol.x, accentCol.y, accentCol.z, 1.0f), O("CALCULATING..."));
        SetWindowFontScale(1.0f);
    }
    End();
    PopStyleVar(2);
    PopStyleColor(2);
}


static void DrawContentArea(float winW, float winH, ImVec2 screenSize) {
    bool need_save = false;
    
    ImDrawList* dl  = GetWindowDrawList();
    ImVec2      wp  = GetWindowPos();
 
    float scaleFactor = GetResponsiveFontScale(GImGui->IO);
    float startY   = GetCursorPosY();
    float contentW = winW;
 
    // Use theme background for content area
    ImVec4 bgCol = g_menu.secondaryColor; // We'll use secondary as panel bg
    bgCol.w = 0.8f; // Slightly transparent
    dl->AddRectFilled(
        ImVec2(wp.x, wp.y + startY),
        ImVec2(wp.x + contentW, wp.y + winH),
        IM_COL32((int)(bgCol.x*255), (int)(bgCol.y*255), (int)(bgCol.z*255), (int)(bgCol.w*255)), 16.0f * scaleFactor
    );
    
    const char* tabTitles[] = { 
    T("draw_settings"), 
    T("auto_play"), 
    T("auto_queue"), 
    T("user") 
    };
 
    const char* currentTitle = tabTitles[g_menu.currentTab];
    float titlePadT = 12.0f * scaleFactor;
    float titlePadB = 8.0f * scaleFactor;
 
    SetWindowFontScale(1.0f * scaleFactor);
    ImVec2 ts = CalcTextSize(currentTitle);
     
    float centeredX = (contentW - ts.x) * 0.5f;
    SetCursorPos(ImVec2(centeredX, startY + titlePadT));
     
    ImVec4 accentCol = g_menu.accentColor;
    TextColored(ImVec4(accentCol.x, accentCol.y, accentCol.z, 1.0f), "%s", currentTitle);
    SetWindowFontScale(1.0f);
 
    float lineY = startY + titlePadT + ts.y + titlePadB;
    // Use accent color for separator line with lower alpha
    dl->AddLine(
        ImVec2(wp.x + 8.0f * scaleFactor, wp.y + lineY),
        ImVec2(wp.x + contentW - 8.0f * scaleFactor, wp.y + lineY),
        IM_COL32((int)(accentCol.x*255), (int)(accentCol.y*255), (int)(accentCol.z*255), 100), 1.0f
    );
 
    float headerH = (lineY - startY) + 6.0f;
    SetCursorPos(ImVec2(8.0f * scaleFactor, startY + headerH));
     
    PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
    BeginChild(T("##ContentArea"), ImVec2(contentW - 16.0f * scaleFactor, winH - startY - headerH - 8.0f), false);
     
    switch (g_menu.currentTab) {
        case 0: {
            Dummy(ImVec2(0, 8 * scaleFactor));
            need_save |= ToggleSwitch(T("draw_lines"), &persistent_bool[O("bESP_DrawPredictionLine")], scaleFactor);
            need_save |= ToggleSwitch(T("draw_pockets"), &persistent_bool[O("bESP_DrawPocketsShotState")], scaleFactor);
 
            Dummy(ImVec2(0, 12 * scaleFactor));
            TextColored(ImVec4(0.70f, 0.70f, 0.75f, 1.0f), T("line_thickness"));
            Dummy(ImVec2(0, 6 * scaleFactor));
            {
                if (persistent_int[O("iLineThickness")] < 1) persistent_int[O("iLineThickness")] = 4;
                PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
                PushStyleVar(ImGuiStyleVar_GrabRounding, 8.0f);
                PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.12f, 0.12f, 0.15f, 1.0f));
                PushStyleColor(ImGuiCol_SliderGrab, ImVec4(g_menu.accentColor.x, g_menu.accentColor.y, g_menu.accentColor.z, 1.0f));
                PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(g_menu.accentColor.x * 0.8f, g_menu.accentColor.y * 0.8f, g_menu.accentColor.z * 0.8f, 1.0f));
                SetNextItemWidth(GetContentRegionAvail().x);
                need_save |= SliderInt(T("##lineThick"), &persistent_int[O("iLineThickness")], 1, 10, "%d");
                PopStyleColor(3);
                PopStyleVar(2);
            }
 
            Dummy(ImVec2(0, 12 * scaleFactor));
            TextColored(ImVec4(0.70f, 0.70f, 0.75f, 1.0f), T("fix_menu_size"));
            Dummy(ImVec2(0, 6 * scaleFactor));
            {
                PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
                PushStyleVar(ImGuiStyleVar_GrabRounding, 8.0f);
                PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.12f, 0.12f, 0.15f, 1.0f));
                PushStyleColor(ImGuiCol_SliderGrab, ImVec4(g_menu.accentColor.x, g_menu.accentColor.y, g_menu.accentColor.z, 1.0f));
                PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(g_menu.accentColor.x * 0.8f, g_menu.accentColor.y * 0.8f, g_menu.accentColor.z * 0.8f, 1.0f));
                SetNextItemWidth(GetContentRegionAvail().x);
                int& menuSz = persistent_int[O("iMenuSizeOffset")];
                bool changed = SliderInt(T("##menuSize"), &menuSz, -10, 10,
                    menuSz == 0 ? T("Normal") : "%d");
                need_save |= changed;
                PopStyleColor(3);
                PopStyleVar(2);
            }
 
            Dummy(ImVec2(0, 16 * scaleFactor));
            {
                PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);
                PushStyleColor(ImGuiCol_Button,        ImVec4(g_menu.accentColor.x * 0.4f, g_menu.accentColor.y * 0.4f, g_menu.accentColor.z * 0.4f, 1.0f));
                PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(g_menu.accentColor.x * 0.5f, g_menu.accentColor.y * 0.5f, g_menu.accentColor.z * 0.5f, 1.0f));
                PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(g_menu.accentColor.x * 0.3f, g_menu.accentColor.y * 0.3f, g_menu.accentColor.z * 0.3f, 1.0f));
                if (Button(T("save_config"), ImVec2(GetContentRegionAvail().x, 45.0f * scaleFactor))) {
                    svConfig_Save();
                }
                PopStyleColor(3);
                PopStyleVar();
            }
            break;
        }
         
        case 1: {
            // AutoPlay tab removed - placeholder
            Dummy(ImVec2(0, 20 * scaleFactor));
            TextColored(ImVec4(0.7f, 0.7f, 0.8f, 1.0f), "Feature removed");
            break;
        }
         
        case 2: {
            // AutoQueue tab removed - placeholder
            Dummy(ImVec2(0, 20 * scaleFactor));
            TextColored(ImVec4(0.7f, 0.7f, 0.8f, 1.0f), "Feature removed");
            break;
        }
         
        case 3: {
            auto DrawSectionHeader = [&](const char* title) {
                Dummy(ImVec2(0, 10 * scaleFactor));
                float avail = GetContentRegionAvail().x;
                ImVec2 p    = GetCursorScreenPos();
                float  fs   = GImGui->FontSize;
                ImVec2 ts   = CalcTextSize(title);
                float  lineY = p.y + fs * 0.5f;
                float  gap   = 6.0f * scaleFactor;
                float  lineW = (avail - ts.x - gap * 2.0f) * 0.5f;
                ImDrawList* dl2 = GetWindowDrawList();
                dl2->AddLine(ImVec2(p.x,                      lineY), ImVec2(p.x + lineW,                      lineY), IM_COL32(70,70,85,160), 1.0f);
                dl2->AddLine(ImVec2(p.x + lineW + gap + ts.x + gap, lineY), ImVec2(p.x + avail, lineY), IM_COL32(70,70,85,160), 1.0f);
                SetCursorPosX(GetCursorPosX() + lineW + gap);
                TextColored(ImVec4(0.55f, 0.55f, 0.65f, 1.0f), "%s", title);
                Dummy(ImVec2(0, 4 * scaleFactor));
            };
 
            auto DrawInfoRow = [&](const char* key, const char* val) {
                TextColored(ImVec4(0.55f, 0.55f, 0.65f, 1.0f), "%s", key);
                SameLine();
                TextColored(ImVec4(0.90f, 0.90f, 0.95f, 1.0f), "%s", val);
                Dummy(ImVec2(0, 3 * scaleFactor));
            };
 
            DrawSectionHeader(T("device"));
            {
                static char s_manufacturer[PROP_VALUE_MAX] = {};
                static char s_model[PROP_VALUE_MAX]        = {};
                static char s_abi[PROP_VALUE_MAX]          = {};
                static char s_android[PROP_VALUE_MAX]      = {};
                static bool s_props_loaded = false;
                if (!s_props_loaded) {
                    __system_property_get("ro.product.manufacturer", s_manufacturer);
                    __system_property_get("ro.product.model",        s_model);
                    __system_property_get("ro.product.cpu.abi",      s_abi);
                    __system_property_get("ro.build.version.release", s_android);
                    s_props_loaded = true;
                }
                DrawInfoRow(T("manufacturer"), s_manufacturer);
                DrawInfoRow(T("model"), s_model);
                DrawInfoRow(T("abi"), s_abi);
                DrawInfoRow(T("android"), s_android);
            }
 
            DrawSectionHeader(T("bradar_s_cheat"));
            {
                int64_t now_ts   = (int64_t)time(nullptr);
                int64_t diff     = EXPIRY_TS - now_ts;
 
                char expireBuf[64];
                if (diff > 0) {
                    int64_t totalSecs = diff;
                    int days  = (int)(totalSecs / 86400);
                    int hours = (int)((totalSecs % 86400) / 3600);
                    int mins  = (int)((totalSecs % 3600)  / 60);
                    snprintf(expireBuf, sizeof(expireBuf), "%dd - %dh - %dm", days, hours, mins);
                } else {
                    snprintf(expireBuf, sizeof(expireBuf), "%s", T("expired"));
                }
 
                DrawInfoRow(T("expire"), expireBuf);
                Dummy(ImVec2(0, 5 * scaleFactor));
                TextColored(ImVec4(0.0f, 1.f, 0.0f, 1.0f), T("owner"));
                Dummy(ImVec2(0, 6 * scaleFactor));
                PushTextWrapPos(GetContentRegionAvail().x + GetCursorPosX());
                TextColored(ImVec4(1.f, 0.f, 0.f, 1.0f),
                    T("beware_scammers"));
                PopTextWrapPos();
            }
            
            // Theme and Language Settings
            DrawSectionHeader(T("settings"));
            {
                // Language selector
                TextColored(ImVec4(0.70f, 0.70f, 0.75f, 1.0f), T("language"));
                Dummy(ImVec2(0, 6 * scaleFactor));
                PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
                PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(12, 10));
                PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.12f, 0.12f, 0.15f, 1.0f));
                PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.16f, 0.16f, 0.20f, 1.0f));
                SetNextItemWidth(GetContentRegionAvail().x);
                
                // Language combo
                const char* language_items[] = {
                    T("language_english"), 
                    T("language_indonesian"),
                    T("language_spanish"),
                    T("language_portuguese"),
                    T("language_turkish"),
                    T("language_vietnamese")
                };
                int& langCombo = *(int*)(&g_currentLanguage); // Hack to use enum as int for combo
                bool lang_changed = Combo(T("##language_combo"), &langCombo, language_items, IM_ARRAYSIZE(language_items));
                if (lang_changed) {
                    g_currentLanguage = static_cast<Language>(langCombo);
                    need_save = true; // Save language preference
                }
                PopStyleColor(2);
                PopStyleVar(2);
                
                Dummy(ImVec2(0, 12 * scaleFactor));
                
                // Theme selector
                TextColored(ImVec4(0.70f, 0.70f, 0.75f, 1.0f), T("theme"));
                Dummy(ImVec2(0, 6 * scaleFactor));
                PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
                PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(12, 10));
                PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.12f, 0.12f, 0.15f, 1.0f));
                PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.16f, 0.16f, 0.20f, 1.0f));
                SetNextItemWidth(GetContentRegionAvail().x);
                
                // Theme combo
                const char* theme_items[] = {
                    T("theme_default"), 
                    T("theme_neon_red"),
                    T("theme_deep_ocean"),
                    T("theme_midnight_purple"),
                    T("theme_gold_edition")
                };
                bool theme_changed = Combo(T("##theme_combo"), &g_currentTheme, theme_items, IM_ARRAYSIZE(theme_items));
                if (theme_changed) {
                    need_save = true; // Save theme preference
                }
                PopStyleColor(2);
                PopStyleVar(2);
            }
            break;
        }
    }
    
    if (need_save) save_persistence();
    
    EndChild();
    PopStyleColor();
}

INLINE void DrawMenu(ImGuiIO& io) {
    if ((!g_Token.empty() && !g_Auth.empty() && g_Token == g_Auth) || DEBUG_BYPASS_LOGIN) {
        // Apply current theme
        ApplyTheme();
        
        if (is_segv_handler_active()) {
            jump_buffer_active = 1;
            if (!sigsetjmp(jump_buffer, 1)) DrawESP(GetBackgroundDrawList());
            jump_buffer_active = 0;
        }

        float targetAlpha = g_menu.isOpen ? 1.0f : 0.0f;
        if (g_menu.isOpen) {
            g_menu.menuAlpha += (1.0f - g_menu.menuAlpha) * io.DeltaTime * 12.0f;
        } else {
            g_menu.menuAlpha = 0.0f;
        }

        if (g_menu.menuAlpha > 0.01f) {
            if (!g_menu.isInitialized) {
                g_menu.sidebarWidth = GetResponsiveWidth(io);
                g_menu.isInitialized = true;
            }
            
            float sizeScale = 1.0f + (float)persistent_int[O("iMenuSizeOffset")] * 0.03f;
            if (sizeScale < 0.3f) sizeScale = 0.3f;
            float winW = g_menu.sidebarWidth * sizeScale;
            float winH = GetResponsiveHeight(io) * sizeScale;
            
            SetNextWindowSize(ImVec2(winW, winH), ImGuiCond_Always);
            SetNextWindowPos(ImVec2(io.DisplaySize.x / 2.0f, io.DisplaySize.y / 2.0f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
            
            // Use theme for window background with alpha
            ImVec4 bgCol = g_menu.secondaryColor; // Using secondary as base
            bgCol.w = 0.0f; // Start transparent, alpha will be applied via style var
            PushStyleColor(ImGuiCol_WindowBg, bgCol);
            PushStyleVar(ImGuiStyleVar_WindowRounding, 16.0f);
            PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            PushStyleVar(ImGuiStyleVar_Alpha, g_menu.menuAlpha);
            
            ImGuiWindowFlags winFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar |
                                        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse |
                                        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            
            if (Begin(T("##MainMenu"), &g_menu.isOpen, winFlags)) {
                DrawSidebar(winW, io.DisplaySize);
                DrawContentArea(winW, winH, io.DisplaySize);
            }
            End();
            
            PopStyleVar(4);
            PopStyleColor();
        }
    }
}



static void DrawFloatingButton(ImGuiIO& io) {
    static GLuint logo_tex   = LoadTextureFromMemory(logo_png, logo_png_len);
    static bool   isDragging = false;

    float scaleFactor = GetResponsiveFontScale(io);
    float buttonRadius = 48.0f * scaleFactor; // Slightly smaller for better proportion
    float buttonSize   = buttonRadius * 2.0f;
    float winSize      = buttonSize + 8.0f;
    float margin       = 6.0f * scaleFactor;

    float toggleWinH = GetFrameHeight() * 1.5f + GetStyle().WindowPadding.y * 2.0f;
    const float rightMargin = 12.0f * scaleFactor;
    float toggleWinW = GetFrameHeight() * 1.5f + GetStyle().WindowPadding.x * 2.0f;
    float fixedX = io.DisplaySize.x - rightMargin - ImMax(winSize, toggleWinW);

    if (g_sideBtnsY == 0.0f)
        g_sideBtnsY = io.DisplaySize.y - 60.0f * scaleFactor - toggleWinH;

    float posY = g_sideBtnsY - winSize - margin;

    SetNextWindowPos(ImVec2(fixedX, posY), ImGuiCond_Always);
    SetNextWindowSize(ImVec2(winSize, winSize), ImGuiCond_Always);
    PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
    PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    if (Begin(T("##FloatBtn"), nullptr,
              ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar |
              ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings)) {

        ImDrawList* dl     = GetWindowDrawList();
        ImVec2      center = ImVec2(fixedX + buttonRadius + 4, posY + buttonRadius + 4);

        SetCursorPos(ImVec2(0, 0));
        InvisibleButton(T("##FloatBtnHit"), ImVec2(winSize, winSize));

        ImVec4 accentCol = g_menu.accentColor;
        dl->AddCircleFilled(center, buttonRadius + 3, IM_COL32(
            (int)(accentCol.x * 80), (int)(accentCol.y * 80), (int)(accentCol.z * 80), 180
        ), 0);
        
        dl->AddImage((void*)(intptr_t)logo_tex,
                     ImVec2(center.x - buttonRadius + 2, center.y - buttonRadius + 2),
                     ImVec2(center.x + buttonRadius - 2, center.y + buttonRadius - 2));

        if (IsItemActive() && IsMouseDragging(0)) {
            isDragging = true;
            g_sideBtnsY += io.MouseDelta.y;
            g_sideBtnsY = ImClamp(g_sideBtnsY, winSize + margin,
                                  io.DisplaySize.y - 60.0f * scaleFactor - toggleWinH);
        }

        if (IsItemHovered() && IsMouseReleased(0) && !isDragging)
            g_menu.isOpen = !g_menu.isOpen;

        if (!IsItemActive()) isDragging = false;
    }
    End();
    PopStyleVar(2);
    PopStyleColor();
}


static bool first_time = true;
INLINE void DrawLogin(ImGuiIO& io) {
    if (logged_in) return DrawMenu(io);

    float scaleFactor = GetResponsiveFontScale(io);

    SetNextWindowPos(ImVec2(0, 0));
    SetNextWindowSize(io.DisplaySize);
    PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.03f, 0.03f, 0.05f, 0.98f));
    Begin(T("##Overlay"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBringToFrontOnFocus);
    PopStyleColor();

    float cardW = 380.0f * scaleFactor;
    float cardH = 340.0f * scaleFactor;

    SetNextWindowSize(ImVec2(cardW, cardH), ImGuiCond_Always);
    SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));

    PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.10f, 0.10f, 0.13f, 1.0f));
    PushStyleVar(ImGuiStyleVar_WindowRounding, 16.0f);
    PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    Begin(T("##LoginCard"), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);

    ImDrawList* dl = GetWindowDrawList();
    ImVec2 winPos = GetWindowPos();
    
    ImVec4 accentCol = g_menu.accentColor;
    DrawGradientRect(dl, winPos, ImVec2(winPos.x + cardW, winPos.y + 85.0f * scaleFactor), 
        IM_COL32((int)(accentCol.x*255), (int)(accentCol.y*255), (int)(accentCol.z*255), 255), 
        IM_COL32((int)(accentCol.x*180), (int)(accentCol.y*180), (int)(accentCol.z*180), 255), true);
    dl->AddRectFilled(winPos, ImVec2(winPos.x + cardW, winPos.y + 16.0f * scaleFactor), 
        IM_COL32((int)(accentCol.x*255), (int)(accentCol.y*255), (int)(accentCol.z*255), 255), 16.0f, ImDrawFlags_RoundCornersTop);

    SetWindowFontScale(1.2f * scaleFactor);
    ImVec2 titleSize = CalcTextSize(T("bradar_s_cheat"));
    dl->AddText(ImVec2(winPos.x + (cardW - titleSize.x) * 0.5f, winPos.y + 22.0f * scaleFactor), IM_COL32(255, 255, 255, 255), T("bradar_s_cheat"));
    SetWindowFontScale(1.0f);
    
    ImVec2 subSize = CalcTextSize(T("free_mod"));
    dl->AddText(ImVec2(winPos.x + (cardW - subSize.x) * 0.5f, winPos.y + 52.0f * scaleFactor), IM_COL32(200, 220, 255, 180), T("free_mod"));

    SetCursorPosY(100.0f * scaleFactor);

    if (!ERROR_MESSAGE.empty()) {
        SetCursorPosX(20.0f * scaleFactor);
        PushTextWrapPos(cardW - 20.0f);
        TextColored(ImVec4(1.0f, 0.4f, 0.4f, 1.0f), "%s", ERROR_MESSAGE.c_str());
        PopTextWrapPos();
        Dummy(ImVec2(0, 12.0f * scaleFactor));
    }

    if (is_logging_in) {
        SetCursorPosY(140.0f * scaleFactor);
        
        static float spinner_angle = 0.0f;
        spinner_angle += io.DeltaTime * 5.0f;

        float spinner_size = 30.0f * scaleFactor;
        ImVec2 spinnerCenter = ImVec2(winPos.x + cardW * 0.5f, winPos.y + 175.0f * scaleFactor);

        for (int i = 0; i < 12; i++) {
            float angle = spinner_angle + (i * PI * 2.0f / 12.0f);
            float alpha = (float)(12 - i) / 12.0f;
            ImVec2 dotPos = ImVec2(
                spinnerCenter.x + cosf(angle) * spinner_size,
                spinnerCenter.y + sinf(angle) * spinner_size
            );
            dl->AddCircleFilled(dotPos, 5.0f * scaleFactor, IM_COL32((int)(accentCol.x*255), (int)(accentCol.y*255), (int)(accentCol.z*255), (int)(alpha * 255)));
        }

        ImVec2 loadingSize = CalcTextSize(T("authenticating"));
        SetCursorPosX((cardW - loadingSize.x) * 0.5f);
        SetCursorPosY(230.0f * scaleFactor);
        TextColored(ImVec4(0.6f, 0.6f, 0.65f, 1.0f), T("authenticating"));
    } else {
        SetCursorPosY(125.0f * scaleFactor);
        
        ImVec2 infoSize = CalcTextSize(T("copy_license_key"));
        SetCursorPosX((cardW - infoSize.x) * 0.5f);
        TextColored(ImVec4(0.55f, 0.55f, 0.6f, 1.0f), T("copy_license_key"));
        
        Dummy(ImVec2(0, 35.0f * scaleFactor));
        
        bool AutoLogin = first_time && !persistent_string["key"].empty();
        
        SetCursorPosX(25.0f * scaleFactor);
        PushStyleColor(ImGuiCol_Button, ImVec4(accentCol.x, accentCol.y, accentCol.z, 1.0f));
        PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(accentCol.x * 1.1f, accentCol.y * 1.1f, accentCol.z * 1.1f, 1.0f));
        PushStyleColor(ImGuiCol_ButtonActive, ImVec4(accentCol.x * 0.9f, accentCol.y * 0.9f, accentCol.z * 0.9f, 1.0f));
        PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);
        
      if (AutoLogin || Button(T("login"), ImVec2(cardW - 50.0f * scaleFactor, 50.0f * scaleFactor))) {
    if (DEBUG_BYPASS_LOGIN) {
        logged_in = true;
        g_menu.isOpen = true;
    } else {
        JNIEnv* env;
        jint getEnvResult = VM->GetEnv((void**)&env, JNI_VERSION_1_6);
        if (getEnvResult == JNI_EDETACHED) {
            if (VM->AttachCurrentThread(&env, nullptr) != 0) ERROR_MESSAGE = T("failed_to_attach_thread");
        } else if (getEnvResult != JNI_OK) {
            ERROR_MESSAGE = T("failed_to_get_jni_env");
        } else {
            std::thread([](std::string androidId, std::string key) {
                Login(androidId, key);
            }, getAndroidID(env), AutoLogin ? persistent_string["key"] : getClipboard(env)).detach();
        }
        first_time = false;
    }
}
         
        PopStyleVar();
        PopStyleColor(3);
         
        Dummy(ImVec2(0, 25.0f * scaleFactor));
         
        ImVec2 helpSize = CalcTextSize(T("your_will_read"));
        SetCursorPosX((cardW - helpSize.x) * 0.5f);
        TextColored(ImVec4(0.42f, 0.42f, 0.48f, 1.0f), T("your_will_read"));
    }

    End();
    PopStyleVar(3);
    PopStyleColor();
    
    End();
}


INLINE void SetupImgui() {
    PACKAGE_NAME = string(getcmdline());

    ImGui::CreateContext();

    auto& style = ImGui::GetStyle();
    auto& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_IsTouchScreen;

    switch_theme(current_theme);

    load_persistence();
    svConfig_Load();
    load_imgui_style();

    static string INI_PATH = O("/data/user_de/0/") + PACKAGE_NAME + O("/no_backup/.ini");
    io.IniFilename = persistent_bool["bImguiAutoSave"] ? INI_PATH.c_str() : nullptr;
    io.ConfigWindowsMoveFromTitleBarOnly = persistent_bool["bMoveOnlyWithTitleBar"];

    ImFontConfig font_cfg;
    font_cfg.SizePixels = persistent_float["fFontScale"];
    io.Fonts->AddFontDefault(&font_cfg);

    ImGui_ImplAndroid_Init();
    ImGui_ImplOpenGL3_Init(O("#version 300 es"));

    style.FrameBorderSize = 0.0f;
    style.WindowBorderSize = 0.0f;
    style.PopupBorderSize = 0.0f;
    style.TabBorderSize = 0.0f;
    style.ScrollbarSize = 6.0f;
    style.GrabMinSize = 8.0f;
    style.FramePadding = ImVec2(8, 6);
    style.ItemSpacing = ImVec2(8, 6);
    style.ItemInnerSpacing = ImVec2(6, 4);
    
    bImguiSetup = true;
}

DEFINES(EGLBoolean, Draw, EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &Width);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &Height);

    if (Width <= 0 || Height <= 0) return _Draw(dpy, surface);

    screenCenter = Vector2(Width / 2, Height / 2);

    if (!bImguiSetup) SetupImgui();

    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(Width, Height);
    ImGui::NewFrame();

    if (!is_segv_handler_active()) setup_global_segv_handler();
    if (IsExpired()) {
        DrawExpired(io);
    } else if ((!g_Token.empty() && !g_Auth.empty() && g_Token == g_Auth) || DEBUG_BYPASS_LOGIN) {
        DrawFloatingButton(io);
        DrawMenu(io);
// "Bradar's Cheat" — Auto-centrat jos
{
    float scaleFactor = io.DisplaySize.x <= 720.0f ? 0.7f : (io.DisplaySize.x <= 1080.0f ? 0.85f : 1.0f);
    float bottomMargin = 20.0f * scaleFactor;
    float fontScale = 0.9f * scaleFactor;
    
    SetNextWindowPos(ImVec2(Width * 0.5f, Height - bottomMargin), ImGuiCond_Always, ImVec2(0.5f, 1.0f));
    
    Begin(O("##PoweredBy"), nullptr, 
          ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | 
          ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | 
          ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize | 
          ImGuiWindowFlags_NoInputs);
    
    SetWindowFontScale(fontScale);
    TextColored(ImVec4(0.0f, 1.0f, 0.0f, 0.8f), O("Owner : @profambatukam"));
    SetWindowFontScale(1.0f);
    
    End();
}

        if (g_autoPlayCalculating) DrawCalculating(io);
    } else {
        DrawLogin(io);
    }
    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui_ClearHoverEffect();

    return _Draw(dpy, surface);
}

void __IMGUI__() {
    create_directory_recursive(CONC(O("/data/user_de/0/"), PACKAGE_NAME.c_str(), O("/no_backup")));
}
