#pragma once
#include "raylib.h"

//window stuff
namespace Window
{
    constexpr int WINDOW_WIDTH = 1280;
    constexpr int WINDOW_HEIGHT = 840;
    constexpr const char* WINDOW_TITLE = "Scrap Run";
}

//layout and tiles
namespace Layout
{
    constexpr int gridHeight = 15;
    constexpr int gridWidth = 20;
    constexpr int tileSize = 48;
    constexpr int topHUDHeight = 50;
    constexpr int bottomHUDHeight = Window::WINDOW_HEIGHT - topHUDHeight - (gridHeight * tileSize);
    constexpr int rightPanelHeight = Window::WINDOW_HEIGHT - topHUDHeight - bottomHUDHeight;
    constexpr int rightPanelWidth = Window::WINDOW_WIDTH - (gridWidth * tileSize);
    constexpr int stashTileX = 0;
    constexpr int stashTileY = 0;
}

//Game Specific
namespace GameSpecific
{
    constexpr float radiationTimer = 90.f;
    constexpr float moveCooldown = 0.15f;
    
    constexpr const char* weaponsCategory = "Weapons";
    constexpr const char* medkitsCategory = "Medkits";
    constexpr const char* rationsCategory = "Rations";
}

