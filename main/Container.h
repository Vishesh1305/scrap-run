#pragma once
#include <vector>
template<typename T, size_t _maxSize_>
class Container
{
private:
	std::vector<T> _items;

public:
	Container() = default;
	
	bool Add(const T&);
	bool Remove(const T&);

	//std::vector<T>::iterator Find();
	//std::vector<T>::const_iterator Find() const;
	
	void Sort(T compA, T compB);
	
	size_t GetCount() const;
	bool IsEmpty() const;
	bool IsFull() const;
	
	std::vector<T>::iterator begin();
	std::vector<T>::const_iterator begin() const;
	std::vector<T>::iterator end();
	std::vector<T>::const_iterator end() const;
};

