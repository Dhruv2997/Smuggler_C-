#pragma once
#include "Item.h"

class City
{

private:
	string name;
public:
	Item* items[Item::NO_OF_ITEMS];

	City(string _name);
	~City();
	void cityDetails();
};

