#pragma once
#include "Item.h"


class Smuggler
{

private:
	int fine;
	int risk;
	int caught;
	string name;

public:
	Item* items[Item::NO_OF_ITEMS];
	int balance;
	int currentCityIndex;
	Smuggler();// - default Constructor
	Smuggler(string _name);
	~Smuggler();//destructor
	int getFine();
	int getRisk();
	int getNumberOfItems();
	void updateRisk();
	string getName();
	bool gotCaught();
	void smugglerStats();
	void showInventory();
};

