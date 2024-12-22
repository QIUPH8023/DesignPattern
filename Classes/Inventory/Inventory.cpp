/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Inventory.cpp
 * File Function: Inventory类的实现
 * Author:        张翔
 * Update Date:   2024/12/7
 ****************************************************************/

#include "Inventory.h"
#include "proj.win32/Constant.h"
#include "proj.win32/Json.hpp"
#include "fstream"

using json = nlohmann::json;

Inventory* Inventory::instance = nullptr;

Inventory::Inventory() :coin(10), currentHeldItemIndex(0) {}

Inventory* Inventory::getInstance() 
{
	if (instance == nullptr) {
		instance = new(std::nothrow)Inventory();
		instance->init(DEFAULT_CAPACITY);
		if (!instance) {
			CC_SAFE_DELETE(instance);
		}
	}
	return instance;
}

void Inventory::init(int slotCount)
{
	slots.resize(slotCount);
	addItem(std::shared_ptr<Item>(ITEM_TOOL_HOE), 1);
	addItem(std::shared_ptr<Item>(ITEM_TOOL_WATERING_CAN), 1);
	addItem(std::shared_ptr<Item>(ITEM_TOOL_PICKAXE), 1);
	addItem(std::shared_ptr<Item>(ITEM_TOOL_AXE), 1);
	addItem(std::shared_ptr<Item>(ITEM_TOOL_SCYTHE), 1);
	addItem(std::shared_ptr<Item>(ITEM_TOOL_FISHING_ROD), 1);

}

int Inventory::findItem(std::shared_ptr<Item> item)
{
	for (int i = 0; i < slots.size(); ++i){
		if (!slots[i].isEmpty() && slots[i].getItem()->getType() == item->getType()){
			// 返回槽位的索引
			return i; 
		}
	}
	return -1;
}

Slot& Inventory::getSlot(int index)
{
	if (index >= 0 && index < slots.size()){
		return slots[index];
	}
	else{
		throw std::out_of_range("Slot index out of range!");
	}
}

int Inventory::getTotalItemCount() const
{
	int totalCount = 0;

	// 遍历所有槽位
	for (const auto& slot : slots)
		if (!slot.isEmpty())
			totalCount++;

	return totalCount;
}

void Inventory::changeCurrHeldItem(int change)
{
	currentHeldItemIndex = change;
}

void Inventory::addItem(std::shared_ptr<Item> item, int quantity)
{
	for (int i = 0; i < slots.size(); i++)
	{
		// 若存在空位
		if (slots[i].isEmpty()) 
		{
			slots[i].setItem(item, quantity);
			break;
		}
		// 若不为空且找到
		if (slots[i].getItem() == item)
		{
			if (item->getMaxStack() >= quantity + slots[i].getQuantity())
			{
				slots[i].changeQuantity(0 - quantity);
			}
			else 
			{
				slots[i].changeQuantity(slots[i].getQuantity() - item->getMaxStack());
			}
			break;
		}
	}

}

bool Inventory::isItemEnough(std::shared_ptr<Item> item, int quantity)
{
	auto currslot = getSlot(findItem(item));
	return currslot.isQuantityEnough(quantity);
}

void Inventory::changeItemQuantity(std::shared_ptr<Item> item, int quantity)
{
	auto currslot = getSlot(findItem(item));
	currslot.changeQuantity(quantity);
}

bool Inventory::swapItems(int index1, int index2)
{
	if (index1 < 0 || index1 >= slots.size() || index2 < 0 || index2 >= slots.size()){
		return false; // 索引越界
	}
	// 交换两个槽位的物品
	std::swap(slots[index1], slots[index2]);
	return true;
}

bool Inventory::isCoinEnough(int price)
{
	return coin >= price;
}

void Inventory::changeCoin(int amount)
{
	coin += amount;
}

int Inventory::getCoin() 
{
	return coin;
}

bool Inventory::isSlotFull() 
{
	for (int i = 0; i < slots.size(); ++i) 
	{
		if (slots[i].isEmpty())
			return false;
	}
	return true;
}

int Inventory::getCurrHeldItem() 
{
	return currentHeldItemIndex;
}

void Inventory::saveInventoryState(const std::string& filename)
{
	json jsonData;

	// 保存金币
	jsonData["coin"] = coin;

	// 保存当前手持物索引
	jsonData["currentHeldItemIndex"] = currentHeldItemIndex;

	// 保存槽位数据
	for (const auto& slot : slots) {
		nlohmann::json slotData;
		
		slotData["quantity"] = slot.getQuantity();
		jsonData["slots"].push_back(slotData);
	}

	// 写入文件
	std::ofstream file(filename);
	if (file.is_open()) {
		file << jsonData.dump(4);
		file.close();
	}
}

void Inventory::loadInventoryState(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) {
		cocos2d::log("Failed to open file: %s", filename.c_str());
		return;
	}

	json jsonData;
	file >> jsonData;
	file.close();

	// 加载金币
	coin = jsonData["coin"].get<int>();

	// 加载当前手持物索引
	currentHeldItemIndex = jsonData["currentHeldItemIndex"].get<int>();

	// 加载槽位数据
	slots.clear(); // 清空当前槽位
	for (const auto& slotData : jsonData["slots"]) {
		int itemID = slotData["itemID"].get<int>();
		int quantity = slotData["quantity"].get<int>();


	}
}
