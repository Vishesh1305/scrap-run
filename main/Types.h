#pragma once
#include <variant>
#include <string>
#include "Core/Item.h"
#include "Core/Container.h"

//Item types
using WeaponItem = Item<std::string>;
using MedkitItem = Item<int>;
using RationItem = Item<float>;

//Container types
using WeaponContainer = Container<WeaponItem, 3>;
using MedkitContainer = Container<MedkitItem, 5>;
using RationContainer = Container<RationItem, 10>;

// Heterogeneous container
using AnyContainer = std::variant<WeaponContainer, MedkitContainer, RationContainer>;

//loose items on the ground
using AnyItem = std::variant<WeaponItem, MedkitItem, RationItem>;