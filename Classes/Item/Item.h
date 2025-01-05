#ifndef _ITEM_H_
#define _ITEM_H_

#include "cocos2d.h"
#include "proj.win32/Constant.h"
#include "string"

// 通用 Item 类
class Item
{
public:
    // 构造函数和析构函数
    Item(ItemType _type, std::string _image, int _maxstack, int _price);
  
    virtual ~Item() = default;

    // 获取物品基本信息
    virtual const ItemType& getType();

    // 获得描述 子类必须覆盖
    virtual const std::string getDescription() = 0 ;

    // 获得基础属性
    std::string getImagePath() const;
    int getMaxStack() const;
    int getprice() const;

protected:
    std::string image;    // 物品素材
    ItemType type;        // 物品类型
    int maxstack;         // 最大堆叠数
    int price;            // 物品价格
};

#endif // _ITEM_H_
