#ifndef _TOOL_H_
#define _TOOL_H_

#include "cocos2d.h"
#include "proj.win32/Constant.h"
#include "Item.h"

class Tool :public Item
{
public:
	// 静态工厂方法：创建 Tool 对象
    static std::shared_ptr<Tool> create(ToolType type, const std::string& image, int maxStack, int price);

	// 获得具体描述
	const std::string getDescription() override;

	// 获得具体类别
	const ToolType& getSubType();

private:
    // 构造函数设置为 private，确保只能通过工厂方法创建实例
    Tool(const ToolType type, const std::string& image, int maxStack, int price);
	
	ToolType tooltype;      // 工具种类

};

#endif // _TOOL_H_
