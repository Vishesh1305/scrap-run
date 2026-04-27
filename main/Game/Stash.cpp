#include "Stash.h"
#include <numeric>

void Stash::Deposit(AnyItem item)
{
    _items.emplace_back(std::move(item));
}

int Stash::GetTotalValue() const
{
    return std::accumulate(_items.begin(), _items.end(), 0, [](int sum, const AnyItem& any) -> int
    {
        return sum + std::visit([](auto& i){return i.GetValue(); }, any);
    });
}

float Stash::GetTotalWeight() const
{
    return std::accumulate(_items.begin(), _items.end(), 0.0f, [](float sum, const AnyItem& any) -> float
{
    return sum + std::visit([](auto& i){return i.GetWeight(); }, any);
});
}

const std::vector<AnyItem>& Stash::GetItems() const
{
    return _items;
}

size_t Stash::GetCount() const
{
    return _items.size();
}
