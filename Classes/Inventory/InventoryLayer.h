#ifndef _INVENTORY_LAYER_H_
#define _INVENTORY_LAYER_H_
#include "cocos2d.h"
#include "Inventory.h"
#include "../Music/AudioPlayer.h"
#include "../Button/HoverButton.h"

class InventoryLayer : public cocos2d::Layer
{
public:
	// 创建一个背包层，初始化背包UI
	static InventoryLayer* create();

	// 初始化
	bool init() override;

	// 关闭背包
	void close();
	
	// 打开背包
	void open();

	~InventoryLayer() override;
};

#endif //_INVENTORY_LAYER_H_
