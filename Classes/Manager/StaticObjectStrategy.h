#ifndef _STATIC_OBJECT_STRATEGY_H_
#define _STATIC_OBJECT_STRATEGY_H_

#include "IGrowthStrategy.h"
#include "FarmObject.h"

class StaticObjectStrategy : public IGrowthStrategy {
private:
    ObjectType objectType;

public:
    explicit StaticObjectStrategy(ObjectType type);

    void initialize(FarmObject* object) override;
    void grow(FarmObject* object) override { /* 静态对象不生长 */ }
    bool isMature(FarmObject* object) override { return true; }
    int getMaxState() const override;
    cocos2d::Rect getCollisionBox(float x, float y) const override;
    std::string getTexturePath(int state) const override;
};

#endif
