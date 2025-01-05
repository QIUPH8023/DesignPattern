
#include "Other.h"

/* 静态工厂方法，用于创建 `Other` 类对象
参数：物品类型、图片路径、最大堆叠数量、物品价格 
返回： 一个共享指针，指向创建的 `Other` 对象
*/
std::shared_ptr<Other> Other::create(OtherType type, const std::string& image, int maxStack, int price) {
    return std::make_shared<Other>(type, image, maxStack, price);
}
Other::Other(const OtherType _othertype, std::string _image, int _maxstack, int _price)
	:Item(ItemType::OTHER, _image, _maxstack, _price), othertype(_othertype) {
}

const std::string Other::getDescription()
{
	switch (othertype) 
	{
		case  FOOD_APPLE:
			return OTHER_FOOD_APPLE_DESCRIPTION;
			break;
		case  FOOD_BREAD:
			return OTHER_FOOD_BREAD_DESCRIPTION;
			break;
		case  FOOD_FRIED_POTATO:
			return OTHER_FOOD_FRIED_POTATO_DESCRIPTION;
			break;
		case  FOOD_FISH:
			return OTHER_FOOD_FISH_DESCRIPTION;
			break;
		case  CROP_RADISH:
			return OTHER_CROP_RADISH_DESCRIPTION;
			break;
		case  CROP_POTATO:
			return OTHER_CROP_POTATO_DESCRIPTION;
			break;
		case  CROP_WHEAT:
			return OTHER_CROP_WHEAT_DESCRIPTION;
			break;
		case  MATERIAL_WOOD:
			return OTHER_MATERIAL_WOOD_DESCRIPTION;
			break;
		case  MATERIAL_STONE:
			return OTHER_MATERIAL_STONE_DESCRIPTION;
			break;
		case  MATERIAL_GRASS:
			return OTHER_MATERIAL_GRASS_DESCRIPTION;
			break;
		case  PRESENT_FLOWER:
			return OTHER_PRESENT_FLOWER_DESCRIPTION;
			break;
		default:
			return " ";
			break;
	}
}

const OtherType& Other::getSubType()
{
	return othertype;
}
