#include "FarmLand.h"

USING_NS_CC;

FarmLand::FarmLand(float _x, float _y) :x(_x), y(_y), landstate(DRY), toRemove(false), dryTime(0) {}

FarmLand::~FarmLand() {}

void FarmLand::update()
{
	// 累计干旱时长
	dryTime++;
	// 根据时长判断耕地状态变化
	if (dryTime >= DRY_THRESHOLD) {
		if (landstate == LandState::WET) {
			landstate = LandState::DRY;
		}
		else if (landstate == LandState::DRY) {
			this->markForRemoval();
		}
	}
}

void FarmLand::watering()
{
	dryTime = 0;
	if (landstate == LandState::DRY) {
		// 将耕地恢复为湿润状态，并重置干旱时间
		landstate = LandState::WET;
	}
}

bool FarmLand::shouldRemove() const
{
	return toRemove;
}

void FarmLand::markForRemoval()
{
	toRemove = true;
}

void FarmLand::setLandState(LandState state)
{
	landstate = state;
}

float FarmLand::getX()
{
	return x;
}

float FarmLand::getY()
{
	return y;
}

LandState FarmLand::getLandState() const
{
	return landstate;
}
