#ifndef _OTHER_H_
#define _OTHER_H_

#include "cocos2d.h"
#include "proj.win32/Constant.h"
#include "Item.h"

class Other : public Item
{
public:
	// 静态工厂方法：创建 Other 对象
    static std::shared_ptr<Other> create(OtherType type, const std::string& image, int maxStack, int price);

	const std::string getDescription() override;

	const OtherType& getSubType();

private:
    // 构造函数设置为 private
    Other(const OtherType type, const std::string& image, int maxStack, int price);
	// 种子
	OtherType othertype;
};

#endif // _SEED_H_
