#include "ItemFactory.h"
#include "Tool.h"
#include "Seed.h"
#include "Other.h"

std::unordered_map<ItemType, std::function<std::shared_ptr<Item>()>> ItemFactory::itemRegistry;

std::shared_ptr<Item> ItemFactory::createItem(ItemType type) {
    /*
    只需在itemRegistry注册新的子类类型即可，无需修改改方法；
    调用方无需关心具体物品的子类，只需传入类型标识。
    */
    auto it = itemRegistry.find(type);
    if (it != itemRegistry.end()) {
        return it->second(); // 调用注册的创建函数
    }
    cocos2d::log("Unknown ItemType: %d", type);
    return nullptr;
}

void ItemFactory::registerItemType(ItemType type, std::function<std::shared_ptr<Item>()> createFunction) {
    itemRegistry[type] = createFunction;
}

// 静态方法：注册所有子类
void ItemFactory::initialize() {
    // 注册 Seed 类型
    registerItemType(SEED, []() {
        return std::make_shared<Seed>(RADISH_SEED, "Items/RADISH_SEED.png", 200, 1);
    });

    // 注册 Other 类型
    registerItemType(OTHER, []() {
        return std::make_shared<Other>(FOOD_APPLE, "Items/FOOD_APPLE.png", 50, 10);
    });

    // 注册 Tool 类型
    registerItemType(TOOL, []() {
        return std::make_shared<Tool>(HOE, "Items/TOOL_HOE.png", 1, 1);
    });
}
