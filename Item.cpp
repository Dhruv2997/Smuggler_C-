#include "Item.h"


Item::Item(string _name, int _buyingPrice, int _sellingPrice, int _quantity)
{
	name = _name;
	buyingPrice = _buyingPrice;
	sellingPrice = _sellingPrice;
	quantity = _quantity;

}

int Item::getBuyingPrice()
{
	return buyingPrice;
}

int Item::getSellingPrice()
{
	return sellingPrice;
}

string Item::getName()
{
	return name;
}
