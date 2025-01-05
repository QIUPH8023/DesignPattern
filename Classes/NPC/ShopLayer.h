#ifndef _SHOP_LAYER_
#define _SHOP_LAYER_

#include "cocos2d.h"
#include "../NPC/ChatLayer.h"
#include "../NPC/NPC.h"
#include "../Item/Item.h"
#include "../proj.win32/Constant.h"
#include "../Inventory/Inventory.h"
#include "../Inventory/InventoryLayer.h"
#include "../Inventory/Slot.h"
#include "../Button/HoverButton.h"
#include "../Item/Seed.h"
#include "../Item/Tool.h"
#include "../Item/Other.h"
#include "../GameTime/ITimeObserver.h"

class ShopLayer : public cocos2d::Layer, public ITimeObserver
{
private:
	NPC* _currentNPC;

	std::vector<std::shared_ptr<Item>>    _ShopItems;       // 商店物品/委托物品
	std::vector<int>      _ShopItemsNum;    // 商店格位数量
	std::vector<ShopType> _ShopItemsType;   // 商店物品操作类型

	// 将ItemType的枚举转变为字符串
	template <typename T>
	std::string enumToString(const T& _itemtype) { return "Unknown"; }

	bool isOpen;  // 商店是否营业
    cocos2d::Label* shopStatusLabel;  // 显示营业状态的标签

public:
	ShopLayer();

	static ShopLayer* create();

	// 初始化
	virtual bool init();

	// 设置对话/交易/委托/赠送的NPC
	void setNPC(NPC* npc);

	// 获取背包物品所在格子
	Slot& getInventorySlots(std::shared_ptr<Item> item);

	// 进行交易 失去PaidItems 得到_ShopItems 返回交易是否成功
	bool tradeItems();

	// 更新商店内物品及其显示
	void UpdateShopItems();

	// 向商店中_ShopItems添加物品
	void InsertShopItems(std::shared_ptr<Item> _item, int num, ShopType type);

	// 清除所有组件
	void DeleteShop();

	// 实现ITimeObserver接口
    virtual void onTimeChanged() override;

    // 检查是否在营业时间
    bool checkBusinessHours();

    // 设置商店状态
    void setShopStatus(bool open);

    virtual ~ShopLayer();

	template <>
	std::string ShopLayer::enumToString<const ItemType&>(const ItemType& _itemtype)
	{
		switch (_itemtype) {
		case SEED:return "SEED";
		case TOOL:return "TOOL";
		case OTHER:return "OTHER";
		default:return "something wrong in ItemType";
		}
	}
	template <>
	std::string ShopLayer::enumToString<const ToolType&>(const ToolType& _itemtype)
	{
		switch (_itemtype) {
		case HOE:return "SEED";
		case WATERING_CAN:return "TOOL";
		case PICKAXE:return "CROP";
		case AXE:return "AXE";
		case SCYTHE:return "SCYTHE";
		case FISHING_ROD:return "FISHING_ROD";
		default:return "something wrong in ToolType";
		}
	}
	template <>
	std::string ShopLayer::enumToString<const SeedType&>(const SeedType& _itemtype)
	{
		switch (_itemtype)
		{
		case RADISH_SEED:return "RADISH_SEED";
		case POTATO_SEED:return "POTATO_SEED";
		case WHEAT_SEED:return "WHEAT_SEED";
		default:return "something wrong in SeedType";
		}
	}

};

#endif // _SHOP_LAYER_
