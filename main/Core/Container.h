#pragma once
#include <vector>
#include <concepts>
#include <algorithm>

template<typename T, size_t N>
class Container
{
private:
	std::vector<T> _items;

public:
	Container() = default;
	
	bool Add(const T& item)
	{
		if (_items.size() >= N) return false;
		_items.push_back(item);
		return true;
	}
	bool Remove(size_t index)
	{
		if (index >= _items.size() || _items.empty()) return false;
		_items.erase(_items.begin() + index);
		return true;
	}
	
	template<typename Pred>
	requires std::predicate<Pred, T>
	typename std::vector<T>::iterator Find(const Pred& predicate)
	{
		return std::find_if(_items.begin(), _items.end(), predicate);
	}
	
	template<typename Pred>
	requires std::predicate<Pred, T>
	typename std::vector<T>::const_iterator Find(const Pred& predicate) const
	{
		return std::find_if(_items.cbegin(), _items.cend(), predicate);
	}
	
	template <typename Comp>
	requires std::predicate<Comp, T, T>
	void Sort(Comp comparator)
	{
		std::sort(_items.begin(), _items.end(), comparator);
	}
	
	size_t GetCount() const
	{
		return _items.size();
	}
	bool IsEmpty() const
	{
		return _items.empty();
	}
	bool IsFull() const
	{
		return _items.size() >= N;
	}
	
	typename std::vector<T>::iterator begin()
	{
		return _items.begin();
	}
	typename std::vector<T>::const_iterator begin() const
	{
		return _items.cbegin();
	}
	typename std::vector<T>::iterator end()
	{
		return _items.end();
	}
	typename std::vector<T>::const_iterator end() const
	{
		return _items.cend();
	}
	
	static constexpr size_t MaxCapacity() { return N; }
	
	void Clear() { _items.clear(); }
};

