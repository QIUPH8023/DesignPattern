#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "../Item/Item.h"
#include "../Item/Other.h"
#include "../Item/Seed.h"
#include "../Item/Tool.h"
#include "Slot.h"
#include "cocos2d.h" 
#include "Component.h"

class Inventory : public Component
{
public:
	Inventory() : coin(10) {}
	
    // 添加槽位
    void add(std::shared_ptr<Component> component) override {
        slots.push_back(component);
    }

    // 移除槽位
    void remove(std::shared_ptr<Component> component) override {
        slots.erase(std::remove(slots.begin(), slots.end(), component), slots.end());
    }

    // 获取槽位
    std::shared_ptr<Component> getChild(int index) const override {
        if (index < 0 || index >= slots.size()) {
            return nullptr;
        }
        return slots[index];
    }

    // 获取金币数量
    int getCoin() const {
        return coin;
    }

    // 修改金币数量
    void changeCoin(int amount) {
        coin += amount;
    }

    // 获取节点名称
    std::string getName() const override {
        return "Inventory";
    }

    // 显示背包信息
    void display() const override {
        printf("Inventory:\n");
        for (const auto& slot : slots) {
            slot->display();
        }
    }

private:
	static Inventory* instance;  // 单例指针
	std::vector<Slot> slots;     // 存储多个槽位
	int currentHeldItemIndex;    // 当前手持物索引
	int coin;                    // 金币数量
	std::vector<std::shared_ptr<Component>> slots;  // 存储槽位

	// 私有构造函数
	Inventory();

};

#endif // _INVENTORY_H_
