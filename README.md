# Scrap Run

A 2D top-down scavenger game built for VGP134 Assignment 1 (Generic Inventory System).

Collect loot across a 20×15 grid before the 90-second radiation timer runs out. Deposit items at your stash to score. Bag space is limited — choose what's worth carrying.

## Assignment Context

Demonstrates C++ templates and STL containers:
- `Item<T>` — generic item template (weapons, medkits, rations)
- `Container<T, MaxSize>` — fixed-capacity inventory with non-type template parameter
- `InventoryManager` — multi-category storage using `std::map` and STL algorithms

Course: VGP134 — Object-Oriented Programming in C++ II
Institution: LaSalle College Vancouver

## Controls

| Key | Action |
|-----|--------|
| WASD | Move |
| E | Pickup / Drop / Deposit |
| TAB | Toggle bag sort |
| P | Pause |
| R | Restart |
| ESC | Quit |

## Build

**Requirements:** Visual Studio 2022, raylib (linked via project config)

1. Open the `.sln` in Visual Studio
2. Select `x64 | Debug` or `x64 | Release`
3. Build and run (F5)

## Credits

- Sprites: [Kenney Tiny Dungeon](https://kenney.nl/assets/tiny-dungeon) (CC0)
- Engine: [raylib](https://www.raylib.com/)
