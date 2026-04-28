#include "InventoryManager.h"
#include <numeric>

bool InventoryManager::AddCategory(const std::string& name, AnyContainer container)
{
    return _categories.emplace(name, std::move(container)).second;
}

bool InventoryManager::AddItem(const std::string& name, const WeaponItem& item)
{
    if (!_categories.contains(name)) return false;
    
    if (auto value = std::get_if<WeaponContainer>(&_categories[name]))
    {
        return value->Add(item);
    }
    return false;
}

bool InventoryManager::AddItem(const std::string& name, const MedkitItem& item)
{
    if (!_categories.contains(name)) return false;
    
    if (auto value = std::get_if<MedkitContainer>(&_categories[name]))
    {
        return value->Add(item);
    }
    return false;
}

bool InventoryManager::AddItem(const std::string& name, const RationItem& item)
{
    if (!_categories.contains(name)) return false;
    
    if (auto value = std::get_if<RationContainer>(&_categories[name]))
    {
        return value->Add(item);
    }
    return false;
}


int InventoryManager::GetTotalValue() const
{
    int total = 0;
    for (const auto& [name, container] : _categories)
    {
        std::visit([&total](auto& c) -> void
        {
            total += std::accumulate(c.begin(), c.end(), 0, [](int sum, const auto& item){return sum + item.GetValue();});
        }, container);
    }
    return total;
}

float InventoryManager::GetTotalWeight() const
{
    float weightTotal = 0.0f;
    for (const auto& [name, container] : _categories)
    {
        std::visit([&weightTotal](auto& c) -> void
        {
            weightTotal += std::accumulate(c.begin(), c.end(), 0.0f, [](float sum, const auto& item){return sum + item.GetWeight();});
        }, container);
    }
    return weightTotal;
    
}

std::vector<AnyItem> InventoryManager::FindItemsByValue(int minValue) const
{
    std::vector<AnyItem> result;
    for (const auto& [name, container] : _categories)
    {
        std::visit([&result, minValue](auto& c) -> void
        {
            std::copy_if(c.begin(), c.end(), std::back_inserter(result), [minValue](auto& item){return item.GetValue() >= minValue;});
        }, container);
    }
    return result;
}

std::vector<AnyItem> InventoryManager::DrainAll()
{
    std::vector<AnyItem> result;
    for (auto& [name, container] : _categories)
    {
        std::visit([&result](auto& c) -> void
        {
            for (auto& item : c)
            {
                result.push_back(std::move(item));
            }
            c.Clear();
        }, container);
    }
    return result;
}

void InventoryManager::SortAllByValue()
{
    auto comparator = [](const auto& a, const auto& b) -> bool {return a.GetValue() > b.GetValue();};
    for (const auto& [name, container] : _categories)
    {
        SortCategory(name, comparator);
    }
}

std::optional<AnyItem> InventoryManager::RemoveFirst()
{
    for (auto& [name, container] : _categories)
    {
        auto result = std::visit([](auto& c) -> std::optional<AnyItem>
        {
            if (!c.IsEmpty())
            {
                AnyItem item = *c.begin();
                c.Remove(0);
                return item;
            }
            return std::nullopt;
        }, container);
        if (result.has_value()) return result;
    }
    return std::nullopt;
}

