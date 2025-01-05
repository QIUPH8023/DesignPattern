#ifndef _I_GROWTH_STRATEGY_H_
#define _I_GROWTH_STRATEGY_H_

#include "cocos2d.h"
#include "proj.win32/Constant.h"

class FarmObject;

class IGrowthStrategy {
public:
    virtual ~IGrowthStrategy() = default;

    // 初始化对象状态
    virtual void initialize(FarmObject* object) = 0;

    // 生长逻辑
    virtual void grow(FarmObject* object) = 0;

    // 判断是否成熟
    virtual bool isMature(FarmObject* object) = 0;

    // 获取最大状态值
    virtual int getMaxState() const = 0;

    // 获取碰撞箱
    virtual cocos2d::Rect getCollisionBox(float x, float y) const = 0;

    // 获取对应状态的纹理路径
    virtual std::string getTexturePath(int state) const = 0;
};

#endif
