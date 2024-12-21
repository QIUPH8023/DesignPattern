/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Tool.h
 * File Function: Tool类的定义
 * Author:        张翔
 * Update Date:   2024/12/14
 ****************************************************************/

#ifndef _TOOL_H_
#define _TOOL_H_

#include "cocos2d.h"
#include "proj.win32/Constant.h"
#include "Item.h"

class Tool :public Item
{
public:
	// 构造函数
	Tool(const ToolType _type, std::string _image, int _maxstack, int _price);

	const std::string getDescription() override;

	const ToolType& getSubType();

	// 工具种类
	ToolType tooltype;

};

// 物品类型
const std::shared_ptr<Tool> ITEM_TOOL_HOE = std::make_shared<Tool>(HOE, "Items/TOOL_HOE.png", 1, 1);
const std::shared_ptr<Tool> ITEM_TOOL_WATERING_CAN = std::make_shared<Tool>(WATERING_CAN, "Items/TOOL_WATERING_CAN.png", 1, 1);
const std::shared_ptr<Tool> ITEM_TOOL_PICKAXE = std::make_shared<Tool>(PICKAXE, "Items/TOOL_PICKAXE.png", 1, 1);
const std::shared_ptr<Tool> ITEM_TOOL_AXE = std::make_shared<Tool>(AXE, "Items/TOOL_AXE.png", 1, 1);
const std::shared_ptr<Tool> ITEM_TOOL_SCYTHE = std::make_shared<Tool>(SCYTHE, "Items/TOOL_SCYTHE.png", 1, 1);
const std::shared_ptr<Tool> ITEM_TOOL_FISHING_ROD = std::make_shared<Tool>(FISHING_ROD, "Items/TOOL_FISHING_ROD.png", 1, 1);

#endif // _TOOL_H_
