/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Object.h
 * File Function: Object类的定义
 * Author:        张翔
 * Update Date:   2024/12/19
 ****************************************************************/

#ifndef _FARMOBJECT_
#define _FARMOBJECT_

#include "cocos2d.h"
#include "../Item/Item.h"
#include "proj.win32/Constant.h"

class FarmObject
{
public:
	// 构造函数
	FarmObject(ObjectType type, float x, float y);

	// 析构函数
	~FarmObject();

	// 成长
	void update();

	// 是否成熟
	bool ismature();

	// 判断是否需要移除
	bool shouldRemove() const;

	// 设置需要移除
	void markForRemoval();

	// 是否被添加到场景
	bool isAddedToScene;

	// 获取精灵
	cocos2d::Sprite* getSprite() const;

	// 获得物品种类
	ObjectType getObjectType() const;

	// 设置当前状态
	void setCurrState(int state);

	// 获取当前阶段
	int getCurrState() const;

	// 对象的碰撞体积
	cocos2d::Rect objectsize;

private:
	cocos2d::Sprite* sprite;  // 对应的精灵
	ObjectType objecttype;    // 对象的种类
	int currstate;            // 当前阶段
	int maxstate;             // 最大阶段
	float growthrate;         // 成长率
	float growthspeed;        // 成长速度
	bool toRemove;            // 是否需要删除

};

#endif // _FARMOBJECT_
