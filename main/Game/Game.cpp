#include "Game.h"
#include "../Renderer/Theme.h"
#include <random>

Game::Game() : 
_state(GameState::Running),
_playerX(Layout::gridWidth / 2),
_playerY(Layout::gridHeight / 2),
_timeRemaining(GameSpecific::radiationTimer),
_moveTimer(0.f)

{
    _playerBag.AddCategory(GameSpecific::weaponsCategory, WeaponContainer{});
    _playerBag.AddCategory(GameSpecific::medkitsCategory, MedkitContainer{});
    _playerBag.AddCategory(GameSpecific::rationsCategory, RationContainer{});
    
    SpawnLoot();
}

void Game::Update(float deltaTime)
{
    if (_state!= GameState::Running) return;
    
    _moveTimer = std::max(0.f, _moveTimer - deltaTime);
    _timeRemaining -= deltaTime;
    if (_timeRemaining <= 0.f)
    {
        _timeRemaining = 0.f;
        _state = GameState::GameOver;
    }
}

void Game::HandleInput()
{
    bool moved = false;
    if (IsKeyPressed(KEY_R))
    {
        Restart();
        return;
    }
    
    if (_state != GameState::Running) return;   
    if (_moveTimer > 0) return;
    
    if (IsKeyDown(KEY_W))
    {
        _playerY--;
        moved = true;
    }
    if (IsKeyDown(KEY_S))
    {
        _playerY++;
        moved = true;
    }
    if (IsKeyDown(KEY_D))
    {
        _playerX++;
        moved = true;
    }
    if (IsKeyDown(KEY_A))
    {
        _playerX--;
        moved = true;
    }
    
    _playerY = std::clamp(_playerY, 0, Layout::gridHeight - 1);
    _playerX = std::clamp(_playerX, 0, Layout::gridWidth - 1);
    
    if (moved) _moveTimer = GameSpecific::moveCooldown;
    
    if (IsKeyPressed(KEY_E))
    {
        if ((_playerX == Layout::stashTileX) && (_playerY == Layout::stashTileY))
        {
            TryDeposit();
        }
        else
        {
            if (!TryPickup()) TryDrop();
        }
    }
    
    if (IsKeyPressed(KEY_TAB))
    {
        _playerBag.SortAllByValue();
    }
    
    
}

bool Game::TryPickup()
{
    const auto it = std::find_if(_loot.begin(), _loot.end(), [this](const auto& lootOnGround)-> bool {return lootOnGround.tileX == this->_playerX && lootOnGround.tileY == this->_playerY;});
    if (it == _loot.end()) return false;
    
    bool added = false;
    if (std::holds_alternative<WeaponItem>(it->item))
    {
        added = _playerBag.AddItem(GameSpecific::weaponsCategory, std::get<WeaponItem>(it->item));
    }
    else if (std::holds_alternative<MedkitItem>(it->item))
    {
        added = _playerBag.AddItem(GameSpecific::medkitsCategory, std::get<MedkitItem>(it->item));
    }
    else
    {
        added = _playerBag.AddItem(GameSpecific::rationsCategory, std::get<RationItem>(it->item));
    }
    
    if (added)
    {
        _loot.erase(it);
        return true;
    }
    return false;
}

bool Game::TryDrop()
{
    if (auto removedItem = _playerBag.RemoveFirst())
    {
        _loot.push_back(LootOnGround{_playerX, _playerY, *removedItem});
        return true;
    }
    return false;
}

bool Game::TryDeposit()
{
    if (!((_playerX == Layout::stashTileX) && (_playerY == Layout::stashTileY))) return false;
    std::vector<AnyItem> items = _playerBag.DrainAll();
    for (auto& it : items)
    {
        _stash.Deposit(std::move(it));
    }
    return true;
}

void Game::Restart()
{
    _state = GameState::Running;
    _playerX = Layout::gridWidth / 2;
    _playerY = Layout::gridHeight / 2;
    _timeRemaining = GameSpecific::radiationTimer;
    _moveTimer = 0.f;
    _loot.clear();
    SpawnLoot();
    _playerBag = InventoryManager{};
    _playerBag.AddCategory(GameSpecific::weaponsCategory, WeaponContainer{});
    _playerBag.AddCategory(GameSpecific::medkitsCategory, MedkitContainer{});
    _playerBag.AddCategory(GameSpecific::rationsCategory, RationContainer{});
    _stash = Stash{};
}

void Game::SpawnLoot()
{
    static const std::vector<WeaponItem> weaponTemplates = 
        {
            WeaponItem("Stormbreaker", "An enchanted Uru battle axe, forged for Thor on Nidavellir", 20, 2.f, "Slashing"),
            WeaponItem("Bent Pipe", "A length of rusted steel. Heavier than it looks.", 15, 2.0f, "Blunt"),
            WeaponItem("Kitchen Knife", "Edge is dull. Still pointy enough.", 20, 0.8f, "Slashing"),
            WeaponItem("Crowbar", "Pried open more doors than skulls. Probably.", 35, 3.0f, "Blunt"),
            WeaponItem("Salvaged Bow", "Strings creak. Aim isn't great past 20 feet.", 50, 1.5f, "Piercing"),
        };
    
    static const std::vector<MedkitItem> medkitTemplates = 
        {
            MedkitItem("Dirty Bandage", "Used. You hope it was washed.", 5, 0.2f, 5),
            MedkitItem("Gauze Roll", "Sealed. Lucky find.", 12, 0.3f, 15),
            MedkitItem("Painkillers", "Three pills left in the bottle.", 20, 0.1f, 25),
            MedkitItem("Stim Shot", "Auto-injector. One use.", 35, 0.4f, 40),
            MedkitItem("Trauma Kit", "Field surgical kit. Sealed.", 60, 1.0f, 75),
        };
    static const std::vector<RationItem> rationTemplates =
        {
        RationItem("Stale Bread", "Hard. Crumbly. Edible.", 3, 0.3f, 10.0f),
        RationItem("Apple", "Bruised but whole.", 5, 0.2f, 15.0f),
        RationItem("Beef Jerky", "Salty. Keeps forever.", 10, 0.2f, 25.0f),
        RationItem("Energy Bar", "Foil's intact. Score.", 12, 0.15f, 30.0f),
        RationItem("Canned Beans", "Dented can. Hopefully not bulged.", 8, 0.6f, 20.0f),
        };
    
    static std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<int> xDist(0, Layout::gridWidth - 1);
    std::uniform_int_distribution<int> yDist(0, Layout::gridHeight - 1);
    std::uniform_int_distribution<int> typeDist(0, 2);  // 0=weapon, 1=medkit, 2=ration
    
    std::uniform_int_distribution<int> weaponIdx(0, static_cast<int>(weaponTemplates.size()) - 1);
    std::uniform_int_distribution<int> medkitIdx(0, static_cast<int>(medkitTemplates.size()) - 1);
    std::uniform_int_distribution<int> rationIdx(0, static_cast<int>(rationTemplates.size()) - 1);
    
    for (int i = 0; i < 12; i++)
    {
        int x = xDist(engine);
        int y = yDist(engine);
        switch (int type = typeDist(engine))
        {
        case 0:
            {
                _loot.push_back({.tileX = x, .tileY = y, .item = weaponTemplates[weaponIdx(engine)]});
                break;
            }
        case 1:
            {
                _loot.push_back({.tileX = x, .tileY = y, .item = medkitTemplates[medkitIdx(engine)]});
                break;
            }
        case 2:
            {
                _loot.push_back({.tileX = x, .tileY = y, .item = rationTemplates[rationIdx(engine)]});
                break;
            }
        default:
            {
                break;
            }
        }
    }
}
