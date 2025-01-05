#pragma once
#include <cocos2d.h>
#include <vector>
#include <string>

// NPC组件接口，定义NPC的基本行为
class NPCComponent {
public:
    virtual ~NPCComponent() {}
    virtual std::string getDialog() = 0;
    virtual void advanceDialog() = 0;
    virtual void setNPCLove(int amount) = 0;
    virtual std::string getNPCLikability() = 0;
};