#include "Renderer.h"
#include "Theme.h"
#include "../Game/Game.h"

Renderer::Renderer()
{
    InitWindow(Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT, Window::WINDOW_TITLE);
    SetTargetFPS(60);
}

Renderer::~Renderer()
{
    CloseWindow();
}

bool Renderer::ShouldClose() const
{
    return WindowShouldClose();
}

void Renderer::Draw(const Game& g) const
{
    BeginDrawing();
    ClearBackground(DARKBROWN);
    
    DrawGrid();
    DrawStashZone();
    DrawLoot(g);
    DrawPlayer(g);
    DrawHUD(g);
    DrawControls();
    DrawBagPanel(g);
    
    if (g.GetState() == GameState::GameOver) DrawGameOver(g);
    
    EndDrawing();
}

void Renderer::DrawGrid() const
{
    for (int y = 0; y < Layout::gridHeight; y++)
        for (int x = 0; x < Layout::gridWidth; x++)
        {
            DrawRectangleLines(x * Layout::tileSize, y * Layout::tileSize + Layout::topHUDHeight, Layout::tileSize, Layout::tileSize, Fade(WHITE, .1f));
        }
}

void Renderer::DrawPlayer(const Game& g) const
{
    DrawRectangle(g.GetPlayerX() * Layout::tileSize, g.GetPlayerY() * Layout::tileSize + Layout::topHUDHeight, Layout::tileSize, Layout::tileSize, SKYBLUE);
}

void Renderer::DrawLoot(const Game& g) const
{
    for (const auto& loot : g.GetLoot())
    {
        Color color = WHITE;
        if (std::holds_alternative<WeaponItem>(loot.item)) color = RED;
        else if (std::holds_alternative<MedkitItem>(loot.item)) color = GREEN;
        else color = YELLOW;
        
        DrawRectangle(loot.tileX * Layout::tileSize, loot.tileY * Layout::tileSize + Layout::topHUDHeight, Layout::tileSize, Layout::tileSize, color);
    }
}

void Renderer::DrawHUD(const Game& g) const
{
    DrawRectangle(0,0,Window::WINDOW_WIDTH, Layout::topHUDHeight, Color{50, 40, 30, 255});
    
    DrawText(TextFormat("Time: %.1f", g.GetTimeRemaining()), 20, 15, 20, WHITE);
    DrawText(TextFormat("Value: %d", g.GetPlayerBag().GetTotalValue()), Window::WINDOW_WIDTH / 3, 15, 20, GOLD);
    DrawText(TextFormat("Weight: %.1f", g.GetPlayerBag().GetTotalWeight()), 2 * Window::WINDOW_WIDTH / 3, 15, 20, SKYBLUE);
}

void Renderer::DrawControls() const
{
    DrawRectangle(0,Window::WINDOW_HEIGHT - Layout::bottomHUDHeight,Window::WINDOW_WIDTH, Layout::bottomHUDHeight, Color{50, 40, 30, 255});
    const char* text = "WASD: Move  |  E: Pickup/Drop/Deposit  |  TAB: Sort  |  R: Restart  |  ESC: Quit";
    int fontSize = 18;
    int textWidth = MeasureText(text, fontSize);
    int x = (Window::WINDOW_WIDTH - textWidth) / 2;
    int y = Window::WINDOW_HEIGHT - Layout::bottomHUDHeight + (Layout::bottomHUDHeight - fontSize) / 2;
    DrawText(text, x, y, fontSize, GRAY);
}

void Renderer::DrawBagPanel(const Game& g) const
{
    int panelX = Layout::gridWidth * Layout::tileSize;
    int panelStartY = Layout::topHUDHeight;
    int y_cursor = panelStartY + 60;
    
    DrawRectangle(Layout::gridWidth * Layout::tileSize, Layout::topHUDHeight, Layout::rightPanelWidth, Layout::rightPanelHeight, Color{50, 40, 30, 255} );
    
    const char* text = "INVENTORY";
    int fontSize = 24;
    int textWidth = MeasureText(text, fontSize);
    int x = panelX + (Layout::rightPanelWidth - textWidth) / 2;
    int y = Layout::topHUDHeight + 15;
    DrawText(text, x, y, fontSize, RAYWHITE);
    
    for (const auto& [name, anyContainer] : g.GetPlayerBag().GetCategories())
    {
        std::visit([&](const auto& c)
        {
            DrawText(TextFormat("%s (%d, %d)",name.c_str(), static_cast<int>(c.GetCount()), static_cast<int>(c.MaxCapacity())), panelX + 10, y_cursor, 18, GOLD);
            y_cursor += 22;
            
            for (const auto& item : c)
            {
                DrawText(TextFormat("  %s", item.GetName().c_str()), panelX + 20, y_cursor, 14, RAYWHITE);
                y_cursor += 18;
            }
            y_cursor += 18;
        }, anyContainer);
    }
}

void Renderer::DrawStashZone() const
{
    DrawRectangle(Layout::stashTileX * Layout::tileSize, Layout::stashTileY * Layout::tileSize + Layout::topHUDHeight, Layout::tileSize, Layout::tileSize, Color{180, 100, 200, 255});
}

void Renderer::DrawGameOver(const Game& g) const
{
    DrawRectangle(0,0,Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT, Fade(BLACK, 0.7f));
    
    const char* title = "GAME OVER";
    int fontSize = 30;
    int textWidth = MeasureText(title, fontSize);
    int x = (Window::WINDOW_WIDTH - textWidth) / 2;
    int y = Window::WINDOW_HEIGHT / 2;
    
    DrawText(title, x, y, fontSize, GRAY);
    
    int scoreFontSize = 20;
    int scoreTextWidth = MeasureText(TextFormat("Final Score: %d", g.GetStash().GetTotalValue()), scoreFontSize);
    int scoreX = (Window::WINDOW_WIDTH - scoreTextWidth) / 2;
    int scoreY = y + fontSize + 25;
    DrawText(TextFormat("Final Score: %d", g.GetStash().GetTotalValue()), scoreX, scoreY, scoreFontSize, GOLD);
    
}
