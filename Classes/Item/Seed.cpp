#include "Seed.h"

/* 静态工厂方法，用于创建 `Seed` 类对象
参数：种子类型、种子图片路径、最大堆叠数量、种子价格
返回：一个共享指针，指向创建的 `Seed` 对象
*/

std::shared_ptr<Seed> Seed::create(SeedType type, const std::string& image, int maxStack, int price) {
    return std::make_shared<Seed>(type, image, maxStack, price);
}
Seed::Seed(const SeedType _seedtype, std::string _image, int _maxstack, int _price)
	:Item(ItemType::SEED, _image, _maxstack, _price), seedtype(_seedtype) {
}

const std::string Seed::getDescription()
{
	switch (seedtype) {
		case  RADISH_SEED:
			return SEED_RADISH_DESCRIPTION;
			break;
		case POTATO_SEED:
			return SEED_POTATO_DESCRIPTION;
			break;
		case  WHEAT_SEED:
			return SEED_WHEAT_DESCRIPTION;
			break;
		default:
			return " ";
			break;
	}
}

const SeedType& Seed::getSubType() 
{
	return seedtype;
}
