/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmObject.cpp
 * File Function: FarmObject类的实现
 * Author:        张翔
 * Update Date:   2024/12/19
 ****************************************************************/

#include "FarmObject.h"

USING_NS_CC;

FarmObject::FarmObject(ObjectType type, float _x, float _y) :x(_x), y(_y), currstate(1), growthrate(0), toRemove(false)
{
	// 设置对象的类型
	objecttype = type;
	// 设置碰撞面积大小
	switch (objecttype){
		case TREE:
			objectsize.setRect(x, y, OBJECT_TREE_WIDTH, OBJECT_TREE_HEIGHT);
			maxstate = 1;
			growthspeed = 0;
			break;
		case WEED:
			objectsize.setRect(x, y, OBJECT_WEED_WIDTH, OBJECT_WEED_HEIGHT);
			maxstate = 1;
			growthspeed = 0;
			break;
		case STONE:
			objectsize.setRect(x, y, OBJECT_STONE_WIDTH, OBJECT_STONE_HEIGHT);
			maxstate = 1;
			growthspeed = 0;
			break;
		case RADISH:
			objectsize.setRect(x, y, OBJECT_CROP_WIDTH, OBJECT_CROP_HEIGHT);
			maxstate = OBJECT_RADISH_MAX_STATE;
			growthspeed = 0.01;
			break;
		case POTATO:
			objectsize.setRect(x, y, OBJECT_CROP_WIDTH, OBJECT_CROP_HEIGHT);
			maxstate = OBJECT_POTATO_MAX_STATE;
			growthspeed = 0.01;
			break;
		case WHEAT:
			objectsize.setRect(x, y, OBJECT_CROP_WIDTH, OBJECT_CROP_HEIGHT);
			maxstate = OBJECT_WHEAT_MAX_STATE;
			growthspeed = 0.01;
			break;
		default:
			break;
	}
}

FarmObject::~FarmObject(){}

void FarmObject::update()
{
	// 如果已经成熟
	if (ismature()) {
		return;
	}
	// 根据成长速度添加成长率
	growthrate += growthspeed;
	if (growthrate >= 1) {
		currstate++;
		growthrate = 0;
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

Rect FarmObject::getSize()const
{
	return objectsize;
}

float FarmObject::getX()
{
	return x;
}

float FarmObject::getY()
{
	return y;
}
