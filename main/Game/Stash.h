#pragma once
#include "../Types.h"
#include <vector>

class Stash
{
private:
    std::vector<AnyItem> _items;

public:
    Stash() = default;
    void Deposit(AnyItem item);
    
    //getters
    int GetTotalValue() const;
    float GetTotalWeight() const;
    const std::vector<AnyItem>& GetItems() const;
    size_t GetCount() const;
};
