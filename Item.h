#pragma once
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

class Item
{

private:
	string name;
	int buyingPrice;
	int sellingPrice;

public:
	static const int NO_OF_ITEMS = 5;
	int quantity;
	Item(string _name, int _buyingPrice, int _sellingPrice, int _quantity);
	int getBuyingPrice();
	int getSellingPrice();
	string getName();
};

