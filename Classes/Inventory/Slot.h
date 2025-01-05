/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Slot.h
 * File Function: Slot类的定义
 * Author:        张翔
 * Update Date:   2024/12/7
 ****************************************************************/

#ifndef _SLOT_
#define _SLOT_

#include <memory>
#include "../Item/Item.h"
#include "Component.h"

class Slot : public Component
{
public:
	Slot() : item(nullptr), quantity(0) {}

	// 构造函数
	Slot();

	// 判断是否为空
	bool isEmpty() const
	{
		return item == nullptr || quantity == 0;
	}

	// 设置物品
	void setItem(std::shared_ptr<Item> _item, int _quantity)
	{
		item = _item;
		quantity = _quantity;
	}

	// 获取当前物品的种类
	std::shared_ptr<Item> getItem() const 
	{
		return item;
	}

	// 删去物品
	void clearSlot()
	{
		item = nullptr;
		quantity = 0;
	}

	// 判断物品是否足够
	bool isQuantityEnough(int amount);

	// 修改物品的数量
	void changeQuantity(int amount) 
	{
		quantity += amount;
		if (quantity <= 0) 
		{
			clearSlot();
		}
	}

	// 获取当前物品的数量
	int getQuantity() const 
	{
		return quantity;
	}

	// 获取节点名称
	std::string getName() const override 
	{
		return item ? item->getImagePath() : "Empty Slot";
	}

private:
	std::shared_ptr<Item> item;  // 该格子存储的物品
	int quantity;                // 物品数量   

};

#endif // _SLOT_
