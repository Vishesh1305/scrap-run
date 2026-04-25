#pragma once
#include <string>
#include <sstream>


template<typename T>
class Item
{
private:
	std::string _name;
	std::string _description;
	int _value;
	float _weight;

	T _data;

public:
	Item(const std::string& name, const std::string& description, int value, float weight, const T& data)
		: _name(name), _description(description), _value(value), _weight(weight), _data(data)
	{
		
	}

	std::string Display() const
	{
		std::ostringstream oss;
		oss << "Name: " << _name << " | " << _description << " | Value: " << _value << " | Weight: " << _weight << " | Data: " << _data ;
		return oss.str();
	}

	//getters 
	const std::string& GetName() const { return _name; }
	const std::string& GetDescription() const { return _description; }
	int GetValue() const { return _value; }
	float GetWeight() const { return _weight; }
	const T& GetData() const { return _data; }
};

