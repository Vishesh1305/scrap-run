#pragma once

#include "Stash.h"
#include "LootOnGround.h"
#include "../Inventory/InventoryManager.h"

enum class GameState
{
    MainMenu,
    Running,
    Paused,
    GameOver
};

class Game
{
private:
    GameState _state;
    
    int _playerX;
    int _playerY;
    float _timeRemaining;
    float _moveTimer;
    
    std::vector<LootOnGround> _loot;
    InventoryManager _playerBag;
    Stash _stash;
public:
    Game();
    
    GameState GetState() const {return _state;}
    int GetPlayerX() const {return _playerX;}
    int GetPlayerY() const {return _playerY;}
    float GetTimeRemaining() const {return _timeRemaining;}
    const std::vector<LootOnGround>& GetLoot() const {return _loot;}
    const InventoryManager& GetPlayerBag() const {return _playerBag;}
    const Stash& GetStash() const {return _stash;}
    
    void Update(float deltaTime);
    void HandleInput();
    
    bool TryPickup();
    bool TryDrop();
    bool TryDeposit();
    
    void Restart();
    
private:
    void SpawnLoot();
};
