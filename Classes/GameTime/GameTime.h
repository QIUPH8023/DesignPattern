#ifndef _GAME_TIME_H_
#define _GAME_TIME_H_

#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include "ITimeObserver.h"

class GameTime : public ISubject
{
private:
	static GameTime* instance;    // 静态实例指针
	int year, month, day;         // 年月日
	int dayofweek;                // 星期
	int hour, minute;             // 具体时间
	double timeSpeed;             // 时间流动速度
	bool running;                 // 控制是否更新时间
	std::vector<ITimeObserver*> observers;  // 观察者列表

	// 构造函数
	GameTime(int y = 1, int m = 1, int d = 1, int h = 6, int min = 0, double speed = 1.0);

	// 规范化时间和日期
	void normalize();

	// 自动更新线程
	void updateLoop();

public:
	// 禁止拷贝和赋值操作
	GameTime(const GameTime&) = delete;
	GameTime& operator=(const GameTime&) = delete;

	// 获取单例实例
	static GameTime* getInstance();

	// 设置时间流速
	void setTimeSpeed(double speed);

	// 控制线程
	void start();
	void stop();

	// 添加时间
	void addSeconds(int realSeconds);

	// 以字符串形式获取时间信息
	std::string toString() const;

	// 判断当前时间
	std::string judgeTime();

	// 到达下一天
	void setnextday();

	// 观察者模式相关方法
	/* 添加观察者到观察者列表
	 * @param observer: 要添加的观察者指针
	 */
	void addObserver(ITimeObserver* observer);

	/* 从观察者列表中移除观察者
	 * @param observer: 要移除的观察者指针
	 */
	void removeObserver(ITimeObserver* observer);

	/* 通知所有观察者时间已更新
	 * 遍历观察者列表调用它们的onTimeChanged方法
	 */
	void notifyObservers();
};

#endif // _GAME_TIME_H_
