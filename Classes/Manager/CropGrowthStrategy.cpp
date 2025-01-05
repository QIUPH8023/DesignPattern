#include "CropGrowthStrategy.h"
#include "FarmObject.h"

CropGrowthStrategy::CropGrowthStrategy(ObjectType type, float speed, int maxState)
    : cropType(type), growthSpeed(speed), maxState(maxState), growthRate(0) {
    stateTextures = getTextureArray();
}

void CropGrowthStrategy::initialize(FarmObject* object) {
    object->setCurrState(1);
}

void CropGrowthStrategy::grow(FarmObject* object) {
    if (!isMature(object)) {
        growthRate += growthSpeed;
        if (growthRate >= 1) {
            object->setCurrState(object->getCurrState() + 1);
            growthRate = 0;
        }
    }
}

bool CropGrowthStrategy::isMature(FarmObject* object) {
    return object->getCurrState() >= maxState;
}

cocos2d::Rect CropGrowthStrategy::getCollisionBox(float x, float y) const {
    return cocos2d::Rect(x, y, OBJECT_CROP_WIDTH, OBJECT_CROP_HEIGHT);
}

std::string CropGrowthStrategy::getTexturePath(int state) const {
    if (state > 0 && state <= maxState && stateTextures) {
        return stateTextures[state - 1];
    }
    return "";
}

const char** CropGrowthStrategy::getTextureArray() const {
    switch (cropType) {
        case RADISH: return OBJECT_RADISH_STATE;
        case POTATO: return OBJECT_POTATO_STATE;
        case WHEAT: return OBJECT_WHEAT_STATE;
        default: return nullptr;
    }
}
