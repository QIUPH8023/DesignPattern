#include "Item.h"

Item::Item(ItemType _type, std::string _image, int _maxstack, int _price)
	:type(_type), image(_image), maxstack(_maxstack), price(_price) {
}

const ItemType& Item::getType()
{
	return type;
}

std::string Item::getImagePath() const
{
	return image;
}

int Item::getMaxStack() const
{
	return maxstack;
}

int Item::getprice() const
{
	return price;
}
