#ifndef _OTHER_H_
#define _OTHER_H_

#include "cocos2d.h"
#include "proj.win32/Constant.h"
#include "Item.h"

class Other : public Item
{
public:
	// 构造函数
	Other(const OtherType _othertype, std::string _image, int _maxstack, int _price);

	const std::string getDescription() override;

	const OtherType& getSubType();


	// 种子
	OtherType othertype;

};

// 物品类型
const std::shared_ptr<Other> ITEM_OTHER_FOOD_APPLE = std::make_shared<Other>(FOOD_APPLE, "Items/FOOD_APPLE.png", 200, 1);
const std::shared_ptr<Other> ITEM_OTHER_FOOD_BREAD = std::make_shared<Other>(FOOD_BREAD, "Items/FOOD_BREAD.png", 200, 1);
const std::shared_ptr<Other> ITEM_OTHER_FOOD_FRIED_POTATO = std::make_shared<Other>(FOOD_FRIED_POTATO, "Items/FOOD_FRIED_POTATO.png", 200, 1);
const std::shared_ptr<Other> ITEM_OTHER_FOOD_FISH = std::make_shared<Other>(FOOD_FISH, "Items/FOOD_FISH.png", 200, 1);
const std::shared_ptr<Other> ITEM_OTHER_CROP_RADISH = std::make_shared<Other>(CROP_RADISH, "Items/CROP_RADISH.png", 200, 1);
const std::shared_ptr<Other> ITEM_OTHER_CROP_POTATO = std::make_shared<Other>(CROP_POTATO, "Items/CROP_POTATO.png", 200, 1);
const std::shared_ptr<Other> ITEM_OTHER_CROP_WHEAT = std::make_shared<Other>(CROP_WHEAT, "Items/CROP_WHEAT.png", 200, 1);
const std::shared_ptr<Other> ITEM_OTHER_MATERIAL_WOOD = std::make_shared<Other>(MATERIAL_WOOD, "Items/MATERIAL_WOOD.png", 200, 1);
const std::shared_ptr<Other> ITEM_OTHER_MATERIAL_STONE = std::make_shared<Other>(MATERIAL_STONE, "Items/MATERIAL_STONE.png", 200, 1);
const std::shared_ptr<Other> ITEM_OTHER_MATERIAL_GRASS = std::make_shared<Other>(MATERIAL_GRASS, "Items/MATERIAL_GRASS.png", 200, 1);
const std::shared_ptr<Other> ITEM_OTHER_PRESENT_FLOWER = std::make_shared<Other>(PRESENT_FLOWER, "Items/PRESENT_FLOWER.png", 200, 1);

#endif // _SEED_H_
