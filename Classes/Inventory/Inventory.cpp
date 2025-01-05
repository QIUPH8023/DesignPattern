#include "Inventory.h"
#include "proj.win32/Constant.h"
#include "proj.win32/Json.hpp"
#include "../Item/Other.h"
#include "../Item/Tool.h"
#include "../Item/Seed.h"
#include "../Factory/ItemFactory.h" 
#include "fstream"

using json = nlohmann::json;

Inventory* Inventory::instance = nullptr;

/*
Inventory类的作用是管理物品而不是负责物品的创建逻辑；
Inventory可以通过ItemFactory创建物品实例，而无需关心具体子类的实现。
*/
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
	// 使用工厂模式添加初始物品
    addItem(ItemFactory::createItem(TOOL), 1); // 创建工具
    addItem(ItemFactory::createItem(SEED), 5); // 创建种子
    addItem(ItemFactory::createItem(OTHER), 10); // 创建其他物品
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

// 修改当前的手持物
void Inventory::changeCurrHeldItem(int change)
{
	currentHeldItemIndex = change;
}

// 添加物品
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

// 判断背包是否装满
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
		// 索引越界
		return false; 
	}
	// 交换两个槽位的物品
	std::swap(slots[index1], slots[index2]);
	return true;
}

// 金币是否足够
bool Inventory::isCoinEnough(int price)
{
	return coin >= price;
}

// 修改金币数量
void Inventory::changeCoin(int amount)
{
	coin += amount;
}

// 获得当前金币数量
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

	// 保存当前手持物品的索引
	jsonData["currentHeldItemIndex"] = currentHeldItemIndex;

	// 保存槽位数据
	for (int i = 0; i < slots.size(); i++) {
		if (slots[i].isEmpty()) {
			continue; // 跳过空槽位
		}

		json slotData;

		// 判断物品的具体类型是什么
		std::shared_ptr<Tool> tool = std::dynamic_pointer_cast<Tool>(slots[i].getItem());
		std::shared_ptr<Seed> seed = std::dynamic_pointer_cast<Seed>(slots[i].getItem());
		std::shared_ptr<Other> other = std::dynamic_pointer_cast<Other>(slots[i].getItem());

		if (tool) {
			slotData["type"] = int(TOOL);
			slotData["subtype"] = int(tool->getSubType());
		}
		else if (seed) {
			slotData["type"] = int(SEED);
			slotData["subtype"] = int(seed->getSubType());
		}
		else if (other) {
			slotData["type"] = int(OTHER);
			slotData["subtype"] = int(other->getSubType());
		}
		else {
			// 如果物品类型不明确，跳过该槽位
			CCLOG("Unknown item type in slot %d", i);
			continue;
		}

		// 写入数量
		slotData["quantity"] = slots[i].getQuantity();

		// 将槽位数据加入数组
		jsonData["slots"].push_back(slotData); 
	}

	// 写入文件
	std::ofstream file(filename);
	if (file.is_open()) {
		file << jsonData.dump(4);  // 格式化为 4 空格的 JSON
		file.close();
	}
	else {
		CCLOG("Failed to open file: %s for saving", filename.c_str());
	}
}

void Inventory::loadInventoryState(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		CCLOG("Failed to open file: %s", filename.c_str());
		return;
	}

	json jsonData;
	try {
		file >> jsonData;
	}
	catch (const json::parse_error& e) {
		CCLOG("Error parsing JSON");
		file.close();
		return;
	}

	file.close();

	// 加载金币
	coin = jsonData.value("coin", 10);  // 如果没有找到字段，默认金币为 10

	// 加载当前手持物品的索引
	currentHeldItemIndex = jsonData.value("currentHeldItemIndex", 0);

	// 加载槽位数据
	if (jsonData.contains("slots")) {
		const auto& slotsData = jsonData["slots"];
		for (const auto& slotData : slotsData) {
			if (!slotData.contains("type") || !slotData.contains("subtype") || !slotData.contains("quantity")) {
				CCLOG("Invalid slot data in file");
				continue;
			}

			int type = slotData["type"].get<int>();
			int subtype = slotData["subtype"].get<int>();
			int quantity = slotData["quantity"].get<int>();

			// 根据物品类型和子类型加载物品
			switch (type) {
			case TOOL:
				switch (subtype) {
				case 0: 
					addItem(ITEM_TOOL_HOE, quantity); 
					break;
				case 1:
					addItem(ITEM_TOOL_WATERING_CAN, quantity);
					break;
				case 2: 
					addItem(ITEM_TOOL_PICKAXE, quantity); 
					break;
				case 3:
					addItem(ITEM_TOOL_AXE, quantity);
					break;
				case 4:
					addItem(ITEM_TOOL_SCYTHE, quantity); 
					break;
				case 5: 
					addItem(ITEM_TOOL_FISHING_ROD, quantity);
					break;
				default: 
					CCLOG("Unknown tool subtype: %d", subtype);
					break;
				}
				break;

			case SEED:
				switch (subtype) {
				case 0: 
					addItem(ITEM_SEED_RADISH_SEED, quantity);
					break;
				case 1:
					addItem(ITEM_SEED_POTATO_SEED, quantity);
					break;
				case 2: 
					addItem(ITEM_SEED_WHEAT_SEED, quantity); 
					break;
				default: 
					CCLOG("Unknown seed subtype: %d", subtype); 
					break;
				}
				break;

			case OTHER:
				switch (subtype) {
				case 0: 
					addItem(ITEM_OTHER_FOOD_APPLE, quantity); 
					break;
				case 1: 
					addItem(ITEM_OTHER_FOOD_BREAD, quantity); 
					break;
				case 2: 
					addItem(ITEM_OTHER_FOOD_FRIED_POTATO, quantity); 
					break;
				case 3:
					addItem(ITEM_OTHER_FOOD_FISH, quantity); 
					break;
				case 4: 
					addItem(ITEM_OTHER_CROP_RADISH, quantity); 
					break;
				case 5:
					addItem(ITEM_OTHER_CROP_POTATO, quantity); 
					break;
				case 6:
					addItem(ITEM_OTHER_CROP_WHEAT, quantity);
					break;
				case 7:
					addItem(ITEM_OTHER_MATERIAL_WOOD, quantity);
					break;
				case 8: 
					addItem(ITEM_OTHER_MATERIAL_STONE, quantity);
					break;
				case 9: 
					addItem(ITEM_OTHER_MATERIAL_GRASS, quantity); 
					break;
				case 10: 
					addItem(ITEM_OTHER_PRESENT_FLOWER, quantity);
					break;
				default: 
					CCLOG("Unknown other item subtype: %d", subtype);
					break;
				}
				break;

			default:
				CCLOG("Unknown item type: %d", type);
				break;
			}
		}
	}
	else {
		CCLOG("No 'slots' field in inventory state file");
	}
}

