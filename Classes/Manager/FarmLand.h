#ifndef _FARMLAND_
#define _FARMLAND_

#include "cocos2d.h"
#include "FarmObject.h"
#include "proj.win32/Constant.h"

class FarmLand
{
public:
	// 构造函数
	FarmLand(float x, float y);

	// 析构函数
	~FarmLand();

	// 更新函数
	void update();

	// 对耕地浇水
	void watering();

	// 判断是否需要移除
	bool shouldRemove() const;

	// 设置需要移除
	void markForRemoval();

	// 修改状态
	void setLandState(LandState state);

	// 获取状态
	LandState getLandState() const;

	// 获取x坐标
	float getX();

	// 获取y坐标
	float getY();

private:
	float x, y;                // 耕地的位置
	LandState landstate;       // 耕地的状态
	int dryTime;               // 当前干旱时间
	bool toRemove;             // 是否要删除

};

#endif // _FARMLAND_
