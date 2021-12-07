
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include "City.h"
#include "Smuggler.h"

using namespace std;

//Function Definitions
void cityInitializer(City* _listOfCities[]);
int getIntInRange(int low, int high);
void drawCar();
void buyFromCity(City* currentCity, Smuggler* smug);
void sellToCity(City* currentCity, Smuggler* smug);
void travelCheck(int* exitPoint, Smuggler* smug);

//Global Variables
const string FORMAT = "\t\t\t\t";
const int NO_OF_CITIES = 10;

int main()
{
    system("COLOR 3F");

    srand(time(0));

    int choice, exit = 1;
    City* listOfCities[NO_OF_CITIES];
    cityInitializer(listOfCities);
    Smuggler* smuggler;

    //Homepage Option for Default or New Smuggler
    cout << FORMAT << "*****************************" << endl << endl;
    cout << FORMAT << "|*Choose Smuggler's Name : *|" << endl << endl;
    cout << FORMAT << "|* 1. Enter Name           *|" << endl << endl;
    cout << FORMAT << "|* 2. Default              *| " << endl << endl;
    cout << FORMAT << "*****************************" << endl << endl;
    cout << FORMAT << "Choice : ";
    choice = getIntInRange(1, 2);

    if (choice == 1)
    {
        string name;
        cout << FORMAT << "Enter Name : ";
        cin >> name;
        smuggler = new Smuggler(name);
    }
    else
    {
        smuggler = new Smuggler();
    }
    cout << endl << FORMAT << "Loading Game...";
    Sleep(300);


    while (exit)
    {
        system("CLS");
        system("COLOR 4F");

        //Displaying the Current City's Information
        cout << endl << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-Your Current City-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
        listOfCities[smuggler->currentCityIndex]->cityDetails();
            
        //Displaying the Smuggler's Information
        cout << endl << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-Smuggler Stats-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << endl;
        smuggler->smugglerStats();
        cout << endl << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;

        //User Menu
        cout << FORMAT << "-------------------------" << endl;
        cout << FORMAT << "|||||||||||MENU||||||||||" << endl;
        cout << FORMAT << "-------------------------" << endl;
        cout << FORMAT << "1. Check Inventory" << endl;
        cout << FORMAT << "-------------------------" << endl;
        cout << FORMAT << "2. Buy From City" << endl;
        cout << FORMAT << "-------------------------" << endl;
        cout << FORMAT << "3. Sell To City" << endl;
        cout << FORMAT << "-------------------------" << endl;
        cout << FORMAT << "4. Travel To New City" << endl;
        cout << FORMAT << "-------------------------" << endl;
        cout << FORMAT << "5. Exit Game" << endl;
        cout << FORMAT << "-------------------------" << endl;
        cout << FORMAT << "Enter Choice :::: ";
        choice = getIntInRange(1, 5);

        switch (choice)
        {
        case 1:
        {
            smuggler->showInventory();
            system("pause");
            break;
        }
        case 2:
        {
            buyFromCity(listOfCities[smuggler->currentCityIndex], smuggler);
            system("pause");
            break;
        }
        case 3:
        {
            sellToCity(listOfCities[smuggler->currentCityIndex], smuggler);
            system("pause");
            break;
        }
        case 4:
        {
            system("CLS");
            drawCar();
            Sleep(500);
            travelCheck(&exit, smuggler);

            break;
        }
        case 5:
        {
            exit = 0;
            break;
        }
        default:
        {
            cout << FORMAT << "Enter Valid Choice Only!" << endl;
            system("pause");
            break;
        }
        }
    }

    delete smuggler;
}


void cityInitializer(City* _listOfCities[])
{
    //List of Names of Cities
    string cities[] = { "Agra", "Vadodra", "Chennai", "Mumbai", "Indore", "Varanasi", "Delhi", "Ahemdabad", "Montreal", "Banglore" };

    //Initializing Cities on the Heap
    for (int i = 0; i < NO_OF_CITIES; i++)
    {
        _listOfCities[i] = new City(cities[i]);
    }
}

void buyFromCity(City* currentCity, Smuggler* smug)
{
    int itemNo, itemQuan, costOfTransaction;
    cout << endl << FORMAT << "Enter Item No. to Buy : ";
    itemNo = getIntInRange(1, Item::NO_OF_ITEMS);
    itemNo = itemNo - 1;

    //Preventing the Smuggler from Buying an item that the City does not have
    while (currentCity->items[itemNo]->quantity == 0)
    {
        cout << endl << FORMAT << "The City does not have any " << currentCity->items[itemNo]->getName() << " to sell! " << endl;
        cout << endl << FORMAT << "Enter Item No. to Buy: ";
        itemNo = getIntInRange(1, Item::NO_OF_ITEMS);
        itemNo = itemNo - 1;
    }

    cout << endl << FORMAT << "Enter Quantity to Buy : ";
    itemQuan = getIntInRange(1, currentCity->items[itemNo]->quantity);

    costOfTransaction = (currentCity->items[itemNo]->getSellingPrice()) * itemQuan;

    //Checking if the Smuggler has enough money to buy the quantity specified
    if (costOfTransaction > smug->balance)
    {
        cout << FORMAT << "Insuffcient Balance For The Transaction!" << endl;
    }
    else
    {
        cout << FORMAT << "Transaction Successfull: you bought " << itemQuan << " Units of " << currentCity->items[itemNo]->getName() << endl;

        //Updating values based on the transaction
        smug->items[itemNo]->quantity += itemQuan;
        currentCity->items[itemNo]->quantity -= itemQuan;
        smug->balance -= costOfTransaction;
        smug->updateRisk();
    }
}

void sellToCity(City* currentCity, Smuggler* smug)
{
    smug->showInventory();
    if (smug->getNumberOfItems() == 0)
    {
        cout << endl << FORMAT << "You Don't Have Anything To Sell!" << endl;
    }
    else {
        int itemNo, itemQuan, costOfTransaction;
        cout << endl << FORMAT << "Enter Item No. to Sell: ";
        itemNo = getIntInRange(1, Item::NO_OF_ITEMS);
        itemNo = itemNo - 1;

        //Preventing the Smuggler from selling something he doesn't have
        while (smug->items[itemNo]->quantity == 0)
        {
            cout << endl << FORMAT << "You do not have any " << smug->items[itemNo]->getName() << " to sell! " << endl;
            cout << endl << FORMAT << "Enter Item No. to Sell: ";
            itemNo = getIntInRange(1, Item::NO_OF_ITEMS);
            itemNo = itemNo - 1;
        }

        cout << endl << FORMAT << "Enter Quantity to sell : ";
        itemQuan = getIntInRange(1, smug->items[itemNo]->quantity);

        costOfTransaction = (currentCity->items[itemNo]->getBuyingPrice()) * itemQuan;

        //Upfating values after the transaction
        currentCity->items[itemNo]->quantity += itemQuan;
        smug->items[itemNo]->quantity -= itemQuan;
        smug->balance += costOfTransaction;
        smug->updateRisk();

        cout << FORMAT << "Transaction Successfull! : You Sold " << itemQuan << " units of " << smug->items[itemNo]->getName() << endl;
    }
}

void travelCheck(int* exitPoint, Smuggler* smug)
{
    int caughtOrNot;

    //Random value between 1-100, if less than risk value, the Smuggler is caught
    caughtOrNot = rand() % 100 + 1;

    if (caughtOrNot <= smug->getRisk())
    {
        //gotCaught() function returns a bool value,if the fine is not collected successfully, it returns false and the game is over
        if (!smug->gotCaught())
        {
            cout << FORMAT << "You don't have enough balance to pay the fine!" << endl;
            cout << FORMAT << "!!!YOU LOSE!!!" << endl;
            *exitPoint = 0;
        }
        system("pause");
    }

    //Using the same integer variable to generate index of new city
    caughtOrNot = rand() % NO_OF_CITIES;

    //checking the index is not of the current city
    while (caughtOrNot == smug->currentCityIndex)
    {
        caughtOrNot = rand() % NO_OF_CITIES;
    }

    smug->currentCityIndex = caughtOrNot;
}

int getIntInRange(int low, int high)
{
    
    double val;
    cin >> val;
    val = (int)val;

    //VALIDATION for the integer values
    while (val > high || val < low || cin.fail())
    {
        cin.clear();
        cin.ignore(512, '\n');
        cout << FORMAT << "Value outside Range, Try Again : ";
        cin >> val;
    }

    return val;
}

//this function is called while the Smuggler is travelling
void drawCar()
{
    cout << FORMAT << "          TRAVELLING...         " << endl;
    cout << FORMAT << "             ___________        " << endl;
    cout << FORMAT << " _ - _ - _ / \______\\__\____   " << endl;
    cout << FORMAT << " _ - _ - _| / , -. - | -, -./-. " << endl;
    cout << FORMAT << "     _ - _ - `( o )----(o)-'    " << endl;
    cout << FORMAT << "               `-'     `-'      " << endl;
}