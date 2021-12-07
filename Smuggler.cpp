#include "Smuggler.h"



Smuggler::Smuggler()
{

	string itemNames[] = { "Milk", "Gem", "Gold", "Ivory", "Silver" };

	//default values
	fine = 100;
	risk = caught = currentCityIndex = 0;
	name = "Bob";
	balance = 2000;

	//initializing items with default values
	for (int i = 0; i < Item::NO_OF_ITEMS; i++)
	{
		items[i] = new Item(itemNames[i], 0, 0, 0);
	}
}

Smuggler::Smuggler(string _name) : Smuggler()
{
	name = _name;
}

Smuggler::~Smuggler()
{
	//deallocating memory of the items 
	for (int i = 0; i < Item::NO_OF_ITEMS; i++)
	{
		delete items[i];
	}
	delete[] items;
}

int Smuggler::getFine()
{
	return fine;
}

int Smuggler::getRisk()
{
	return risk;
}

void Smuggler::updateRisk()
{
	//updating risk value based on the number of items
	risk = getNumberOfItems() * 5;
}

string Smuggler::getName()
{
	return name;
}

bool Smuggler::gotCaught()
{
	cout << endl << "\t\t\t\t" << "YOU GOT CAUGHT!!!" << endl;
	caught++;
	if (fine > balance)
		return false;
	else
	{	//checking for the items Smuggler has, and setting one of item's quantity to 0
		int randIndex = rand() % Item::NO_OF_ITEMS;
		while (items[randIndex]->quantity == 0) {
			randIndex = rand() % Item::NO_OF_ITEMS;
		}
		items[randIndex]->quantity = 0;


		cout << endl << "\t\t\t\t" << "All your " << items[randIndex]->getName() << " is being Seized!" << endl;
		cout << endl << "\t\t\t\t" << "You've Been Charged A Fine Of $" << fine << endl;

		//updating relevant fields
		updateRisk();
		balance = balance - fine;
		fine += 50;
		return true;
	}
}

void Smuggler::smugglerStats()
{
	cout << endl << "\tName: " << name << "\t\tMoney: $" << balance << "\t\tRisk: " << risk << "%\t\tCaught: " << caught << " times" << endl;
}

void Smuggler::showInventory()
{
	cout << endl << "\t\t*********************************************************";
	cout << endl << "\t\t\tItem No.\tItem Name \t Quantity" << endl;
	for (int i = 0; i < Item::NO_OF_ITEMS; i++)
	{
		cout << endl << "\t\t\t" << i + 1 << "\t\t" << items[i]->getName() << "\t\t\t" << items[i]->quantity << endl;
	}
	cout << endl << "\t\t*********************************************************" << endl;
}

int Smuggler::getNumberOfItems()
{
	int noOfItems = 0;
	for (int i = 0; i < Item::NO_OF_ITEMS; i++)
	{
		noOfItems += items[i]->quantity;
	}
	return noOfItems;
}