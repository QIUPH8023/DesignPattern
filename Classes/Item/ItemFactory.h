#ifndef _ITEM_FACTORY_H_
#define _ITEM_FACTORY_H_

#include "Item.h"
#include <memory>
#include <functional>
#include <unordered_map>

/*
 工厂模式的核心原因：集中管理所有子类实例化逻辑
1. ItemFactory 是工厂模式的实现，用于统一管理不同类型物品的创建逻辑。
2. Inventory通过工厂创建物品，而无需直接依赖具体子类
3. 动态注册机制使得扩展新的物品类型时无需修改核心代码。
*/

class ItemFactory {
public:
    // 创建 Item 对象（根据 ItemType）
    static std::shared_ptr<Item> createItem(ItemType type);

    // 注册新类型及其创建逻辑
    static void registerItemType(ItemType type, std::function<std::shared_ptr<Item>()> createFunction);

    // 初始化方法，用于注册所有已知类型
    static void initialize();

private:
    static std::unordered_map<ItemType, std::function<std::shared_ptr<Item>()>> itemRegistry; // 注册表
};

#endif // _ITEM_FACTORY_H_
