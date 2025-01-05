#ifndef _GAME_TIME_LAYER_H_
#define _GAME_TIME_LAYER_H_

#include "cocos2d.h"
#include "../GameTime/GameTime.h"
#include "ITimeObserver.h"

class GameTimeLayer :public cocos2d::Layer, public ITimeObserver
{
public:
	// 初始化
	virtual bool init() override;

	// 创建函数
	CREATE_FUNC(GameTimeLayer);

	// 更新时间
	void updateTime(float delta);

	/* 实现ITimeObserver接口的更新方法
	 * 当游戏时间发生变化时被调用
	 */
	virtual void onTimeChanged() override;

	// 析构函数
	virtual ~GameTimeLayer();

private:

	// 显示时间的标签
	cocos2d::Label* timeLabel;

	// 显示时间图标的精灵
	cocos2d::Sprite* timeIcon;

};

#endif // _GAME_TIME_LAYER_H_