/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmObject.cpp
 * File Function: FarmObject类的实现
 * Author:        张翔
 * Update Date:   2024/12/19
 ****************************************************************/

#include "FarmObject.h"

USING_NS_CC;

FarmObject::FarmObject(ObjectType type, float x, float y) :sprite(nullptr), currstate(1), growthrate(0), toRemove(false), isAddedToScene(false)
{
	// 设置对象的类型
	objecttype = type;
	// 设置碰撞面积大小
	switch (objecttype){
		case TREE:
			objectsize.setRect(x, y, OBJECT_TREE_WIDTH, OBJECT_TREE_HEIGHT);
			sprite = Sprite::create("ImageElements/FarmObjects/Tree1State_1.png");
			maxstate = 1;
			growthspeed = 0;
			break;
		case WEED:
			objectsize.setRect(x, y, OBJECT_WEED_WIDTH, OBJECT_WEED_HEIGHT);
			sprite = Sprite::create("ImageElements/FarmLands/DrySoil.png");
			maxstate = 1;
			growthspeed = 0;
			break;
		case STONE:
			objectsize.setRect(x, y, OBJECT_STONE_WIDTH, OBJECT_STONE_HEIGHT);
			sprite = Sprite::create("ImageElements/FarmLands/DrySoil.png");
			maxstate = 1;
			growthspeed = 0;
			break;
		case RADISH:
			objectsize.setRect(x, y, OBJECT_CROP_WIDTH, OBJECT_CROP_HEIGHT);
			sprite = Sprite::create("ImageElements/FarmObjects/RadishState_1.png");
			maxstate = OBJECT_RADISH_MAX_STATE;
			growthspeed = 0.1;
			break;
		case POTATO:
			objectsize.setRect(x, y, OBJECT_CROP_WIDTH, OBJECT_CROP_HEIGHT);
			sprite = Sprite::create("ImageElements/FarmObjects/PotatoState_1.png");
			maxstate = OBJECT_POTATO_MAX_STATE;
			growthspeed = 0.1;
			break;
		case WHEAT:
			objectsize.setRect(x, y, OBJECT_CROP_WIDTH, OBJECT_CROP_HEIGHT);
			sprite = Sprite::create("ImageElements/FarmObjects/WheatState_1.png");
			maxstate = OBJECT_WHEAT_MAX_STATE;
			growthspeed = 0.1;
			break;
		default:
			break;
	}
	if (sprite != nullptr) {
		sprite->setAnchorPoint(Vec2(0, 0));
		sprite->setPosition(x, y);
		sprite->setCameraMask(unsigned short(CameraFlag::USER1));
	}
}

FarmObject::~FarmObject(){}

void FarmObject::update()
{
	// 如果已经成熟
	if (ismature())
		return;

	// 根据成长速度添加成长率
	growthrate += growthspeed;
	if (growthrate >= 1) {
		currstate++;
		growthrate = 0;
		switch (objecttype) {
			case RADISH:
				sprite->setTexture(OBJECT_RADISH_STATE[currstate - 1]);
				break;
			case POTATO:
				sprite->setTexture(OBJECT_POTATO_STATE[currstate - 1]);
				break;
			case WHEAT:
				sprite->setTexture(OBJECT_WHEAT_STATE[currstate - 1]);
				break;
			default:
				break;
		}
	}
}

bool FarmObject::ismature()
{
	return currstate == maxstate;
}

bool FarmObject::shouldRemove() const
{
	return toRemove;
}

void FarmObject::markForRemoval()
{
	toRemove = true;
}

Sprite* FarmObject::getSprite() const
{
	return sprite;
}

ObjectType FarmObject::getObjectType() const
{
	return objecttype;
}

void FarmObject::setCurrState(int state)
{
	currstate = state;
}

int FarmObject::getCurrState() const
{
	return currstate;
}
