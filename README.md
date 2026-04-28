# Scrap Run

A 2D top-down scavenger game. Collect loot across a 20×15 grid before the radiation timer runs out. Deposit items at your stash to score. Bag space is limited per category you choose what's worth carrying.

## Demo

https://github.com/user-attachments/assets/09d58bf2-0185-499b-9016-2dae204575f0

## Gameplay

You have 60 seconds. Loot is scattered across the grid in three categories: **weapons**, **medkits**, and **rations**. Each category has its own bag capacity (3 / 5 / 10). Pick items up with E, walk back to the stash zone in the top-left, deposit with E. Score is the total value of everything deposited before the timer hits zero.

If your bag is full, you can drop items back to the ground to make room.

## Controls

| Key | Action |
|-----|--------|
| WASD | Move |
| E | Pickup / Drop / Deposit (context-sensitive) |
| TAB | Sort bag by value (descending) |
| R | Restart |
| ESC | Quit |

## Build

**Requirements:** Visual Studio 2022, raylib (linked via project config)

1. Open the `.sln` in Visual Studio
2. Select `x64 | Debug` or `x64 | Release`
3. Build and run (F5)

## Roadmap

### Shipped
- Generic `Item<T>` template (weapons, medkits, rations)
- `Container<T, MaxSize>` with compile-time capacity
- `InventoryManager` using `std::map` and `std::variant` for heterogeneous containers
- Full gameplay loop: pickup, drop, deposit, sort, restart
- Game over screen with final score
- Tile-based movement with cooldown

### Planned
- Pause + main menu states
- Sprite swap (Kenney Tiny Dungeon) + level design pass
- Player speed scales with carried weight
- High score persistence (file I/O)
- UI polish to match new visual language
- Audio (SFX + ambient)

### In planning
- Volatility mechanic: some form of in-grid pressure beyond the timer (enemies, hotspots, item decay, or something else). Design question first: what player decision does it create that the game doesn't already have? Build only if the answer is clear.

## Assignment Context

Originally built for VGP134 Assignment 1 (Generic Inventory System) at LaSalle College Vancouver. Demonstrates C++ templates and STL containers via the inventory system. Now being extended as a portfolio piece.

## Credits

- Sprites: [Kenney Tiny Dungeon](https://kenney.nl/assets/tiny-dungeon) (CC0) — pending integration
- Engine: [raylib](https://www.raylib.com/)

---

Made by Vishesh.