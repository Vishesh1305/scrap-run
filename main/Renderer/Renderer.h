#pragma once

class Game;

class Renderer
{
    
public:
    Renderer();
    ~Renderer();
    
    //deleting copy constructor and copy assignemet to avoid copies
    Renderer(const Renderer& other) = delete;
    Renderer& operator=(const Renderer& other) = delete;
    
    bool ShouldClose() const;
    void Draw(const Game& g) const;
    
private:
    void DrawGrid() const;
    void DrawPlayer(const Game& g) const;
    void DrawLoot(const Game& g) const;
    void DrawHUD(const Game& g) const;
    void DrawControls() const;
    void DrawBagPanel(const Game& g) const;
};
