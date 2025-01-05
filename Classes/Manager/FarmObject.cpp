/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmObject.cpp
 * File Function: FarmObject类的实现
 * Author:        张翔
 * Update Date:   2024/12/19
 ****************************************************************/

#include "FarmObject.h"
#include "Strategy/CropGrowthStrategy.h"
#include "Strategy/StaticObjectStrategy.h"

USING_NS_CC;

FarmObject::FarmObject(ObjectType type, float _x, float _y)
    : x(_x), y(_y), objecttype(type), toRemove(false)
{
    // 根据对象类型选择对应的策略
    switch (type) {
        case RADISH:
            growthStrategy = new CropGrowthStrategy(0.01f, OBJECT_RADISH_MAX_STATE);
            break;
        case POTATO:
            growthStrategy = new CropGrowthStrategy(0.01f, OBJECT_POTATO_MAX_STATE);
            break;
        case WHEAT:
            growthStrategy = new CropGrowthStrategy(0.01f, OBJECT_WHEAT_MAX_STATE);
            break;
        default:
            growthStrategy = new StaticObjectStrategy(type);
    }

    objectsize = growthStrategy->getCollisionBox(x, y);
    growthStrategy->initialize(this);
}

FarmObject::~FarmObject() {
    delete growthStrategy;
}

void FarmObject::update() {
    growthStrategy->grow(this);
}

bool FarmObject::ismature() {
    return growthStrategy->isMature(this);
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
