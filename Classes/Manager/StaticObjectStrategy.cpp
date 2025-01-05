#include "StaticObjectStrategy.h"
#include "FarmObject.h"

StaticObjectStrategy::StaticObjectStrategy(ObjectType type) : objectType(type) {}

void StaticObjectStrategy::initialize(FarmObject* object) {
    object->setCurrState(1);
}

void StaticObjectStrategy::grow(FarmObject* object) {
    // 静态对象不需要生长
}

bool StaticObjectStrategy::isMature(FarmObject* object) {
    return true;  // 静态对象总是被视为成熟状态
}

int StaticObjectStrategy::getMaxState() const {
    return 1;
}

cocos2d::Rect StaticObjectStrategy::getCollisionBox(float x, float y) const {
    switch(objectType) {
        case TREE:
            return cocos2d::Rect(x, y, OBJECT_TREE_WIDTH, OBJECT_TREE_HEIGHT);
        case STONE:
            return cocos2d::Rect(x, y, OBJECT_STONE_WIDTH, OBJECT_STONE_HEIGHT);
        case WEED:
            return cocos2d::Rect(x, y, OBJECT_WEED_WIDTH, OBJECT_WEED_HEIGHT);
        default:
            return cocos2d::Rect(x, y, 0, 0);
    }
}

std::string StaticObjectStrategy::getTexturePath(int state) const {
    switch(objectType) {
        case TREE:
            return "ImageElements/FarmObjects/Tree1State_1.png";
        case STONE:
            return "ImageElements/FarmObjects/StoneState_1.png";
        case WEED:
            return "ImageElements/FarmObjects/WeedState_1.png";
        default:
            return "";
    }
}
