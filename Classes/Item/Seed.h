#ifndef _SEED_H_
#define _SEED_H_

#include "cocos2d.h"
#include "proj.win32/Constant.h"
#include "Item.h"

class Seed : public Item
{
public:
	 // 静态工厂方法：创建 Seed 对象
    static std::shared_ptr<Seed> create(SeedType type, const std::string& image, int maxStack, int price);

	// 获得具体描述
	const std::string getDescription() override;

	// 获得具体类别
	const SeedType& getSubType();

private:
	// 构造函数设置为 private
    Seed(const SeedType type, const std::string& image, int maxStack, int price);
	SeedType seedtype;    // 种子

};

#endif // _SEED_H_
