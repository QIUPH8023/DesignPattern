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
	FarmObject(ObjectType type, float _x, float _y);

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

	// 获得物品种类
	ObjectType getObjectType() const;

	// 设置当前状态
	void setCurrState(int state);

	// 获取当前阶段
	int getCurrState() const;

	// 获取碰撞体积
	cocos2d::Rect getSize()const;

	// 获取x坐标
	float getX();

	// 获取y坐标
	float getY();

private:
	float x, y;                  // 对象的位置
	ObjectType objecttype;       // 对象的种类
	int currstate;               // 当前阶段
	int maxstate;                // 最大阶段
	cocos2d::Rect objectsize;    // 对象的碰撞体积
	float growthrate;            // 成长率
	float growthspeed;           // 成长速度
	bool toRemove;               // 是否需要删除

};

#endif // _FARMOBJECT_
