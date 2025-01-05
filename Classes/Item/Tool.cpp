#include "Tool.h"

/* 静态工厂方法，用于创建 `Tool` 类对象
参数：工具类型、工具图片路径、最大堆叠数量、工具价格
返回：一个共享指针，指向创建的 `Tool` 对象
*/

std::shared_ptr<Tool> Tool::create(ToolType type, const std::string& image, int maxStack, int price) {
    return std::make_shared<Tool>(type, image, maxStack, price);
}
Tool::Tool(const ToolType _tooltype, std::string _image, int _maxstack, int _price)
	:Item(ItemType::TOOL, _image, _maxstack, _price), tooltype(_tooltype) {
}

const std::string Tool::getDescription()
{
	switch (tooltype) {
		case  HOE:
			return TOOL_HOE_DESCRIPTION;
			break;
		case WATERING_CAN:
			return TOOL_WATERING_CAN_DESCRIPTION;
			break;
		case   PICKAXE:
			return TOOL_PICKAXE_DESCRIPTION;
			break;
		case  AXE:
			return TOOL_AXE_DESCRIPTION;
			break;
		case  SCYTHE:
			return TOOL_SCYTHE_DESCRIPTION;
			break;
		case FISHING_ROD:
			return TOOL_FISHING_ROD_DESCRIPTION;
			break;
		default:
			return " ";
			break;
	}
}

const ToolType& Tool::getSubType() 
{
	return tooltype;
}
