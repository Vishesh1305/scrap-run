#pragma once
#include <map>
#include "../Types.h"
#include <optional>

class InventoryManager
{
private:
    std::map<std::string, AnyContainer> _categories;
public:
    bool AddCategory(const std::string& name, AnyContainer container);
    
    bool AddItem(const std::string& name, const WeaponItem& item);
    bool AddItem(const std::string& name, const MedkitItem& item);
    bool AddItem(const std::string& name, const RationItem& item);
    
    int GetTotalValue() const;
    float GetTotalWeight() const;
    
    const std::map<std::string, AnyContainer>& GetCategories() const { return _categories; }
    
    std::vector<AnyItem> FindItemsByValue(int minValue) const;
    std::vector<AnyItem> DrainAll();
    
    template<typename Comp>
    bool SortCategory(const std::string& name, Comp comparator)
    {
        if (!_categories.contains(name)) return false;
        
        std::visit([&comparator](auto& c)
        {
            c.Sort(comparator);
        }, _categories[name]);
        return true;
    }
    /*
     * Note: the caller must pass a comparator matching the category's item type other it will throw a nasty error.
     * meaning, if you are calling this method for "medkits" then it will expect a comparator but if you pass in a weaponItem or a RationItem in it, it will throw. 
     */
    
    void SortAllByValue();
    std::optional<AnyItem> RemoveFirst();
    
};
