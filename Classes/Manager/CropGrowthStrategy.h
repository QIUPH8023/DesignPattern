#ifndef _CROP_GROWTH_STRATEGY_H_
#define _CROP_GROWTH_STRATEGY_H_

#include "IGrowthStrategy.h"
#include "proj.win32/Constant.h"

class CropGrowthStrategy : public IGrowthStrategy {
private:
    float growthSpeed;
    int maxState;
    float growthRate;
    ObjectType cropType;
    const char** stateTextures;

public:
    CropGrowthStrategy(ObjectType type, float speed, int maxState);

    void initialize(FarmObject* object) override;
    void grow(FarmObject* object) override;
    bool isMature(FarmObject* object) override;
    int getMaxState() const override;
    cocos2d::Rect getCollisionBox(float x, float y) const override;
    std::string getTexturePath(int state) const override;

private:
    // 根据作物类型获取对应的纹理数组
    const char** getTextureArray() const;
};

#endif

// filepath: /d:/Design Pattern/Stardew_Valley_Farm/Classes/Manager/Strategy/StaticObjectStrategy.h
class StaticObjectStrategy : public IGrowthStrategy {
public:
    void grow(FarmObject* object) override { /* 静态对象不生长 */ }
    void update(FarmObject* object) override { /* 无需更新 */ }
    bool isMature(FarmObject* object) override { return true; }
    int getMaxState() const override { return 1; }
};
