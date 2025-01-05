#pragma once
#include <cocos2d.h>

// 定义场景组件接口，所有场景类将实现这个接口
class SceneComponent : public cocos2d::Scene {
public:
    virtual ~SceneComponent() {}
    virtual cocos2d::Scene* createScene() = 0;
    virtual bool init() = 0;
    virtual void update(float delta) = 0;
};