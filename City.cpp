#include "City.h"

City::City(string _name)
{
	int  sp, bp, quant;
	string itemNames[] = { "Milk", "Gem", "Gold", "Ivory", "Silver" };
	name = _name;
	for (int i = 0; i < Item::NO_OF_ITEMS; i++)
	{
		bp = rand() % 50 + 50;
		sp = rand() % 50 + bp;
		quant = rand() % 10 + 1;
		items[i] = new Item(itemNames[i], bp, sp, quant);
	}
}

City::~City()
{
	for (int i = 0; i < Item::NO_OF_ITEMS; i++)
	{
		delete items[i];
	}
	delete[] items;
}

void City::cityDetails() {

	cout << endl << "\tCITY NAME --- " << name << endl;

	cout << endl << "\tItem No.\tItem Name \t Buying Price \t Selling Price \t   Quantity" << endl;
	for (int i = 0; i < Item::NO_OF_ITEMS; i++)
	{
		cout << endl << "\t" << i + 1 << "\t\t" << items[i]->getName() << "\t\t\t" << items[i]->getBuyingPrice() << "\t\t" << items[i]->getSellingPrice() << "\t\t" << items[i]->quantity << endl;
	}

}