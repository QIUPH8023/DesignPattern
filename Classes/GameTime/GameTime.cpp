#include "GameTime.h"
#include "cocos2d.h"

 // 静态实例初始化
GameTime* GameTime::instance = nullptr;

 // 获取单例实例
GameTime* GameTime::getInstance()
{
	if (instance == nullptr) {
		// 使用 nothrow 分配内存
		instance = new (std::nothrow) GameTime();
		// 初始化失败则销毁实例
		if (!instance) {
			CC_SAFE_DELETE(instance);
		}
	}
	return instance;
}

GameTime::GameTime(int y, int m, int d, int h, int min, double speed) :year(y), month(m), day(d), dayofweek(1), hour(h), minute(min), timeSpeed(speed), running(false)
{
	normalize();
}

void GameTime::normalize()
{
	if (minute >= 60){
		minute = 0;
		hour++;
		if (hour >= 24) {
			hour = 0;
			day++;
			dayofweek++;
			if (dayofweek > 7) {
				dayofweek = 1;
			}
			if (day > 30) {
				day = 1;
				month++;
				if (month > 4) {
					month = 1;
					year++;
				}
			}
		}
	}
	// 如果时间有错就重新更新
	if (minute >= 60 || hour >= 24 || day > 30 || month > 4) {
		GameTime::normalize();
	}
}

void GameTime::updateLoop()
{
	while (running) {
		// 更新间隔
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		// 添加时间
		addSeconds(1);
	}
}

void GameTime::setTimeSpeed(double speed)
{
	timeSpeed = speed;
}

void GameTime::start()
{
	running = true;
	std::thread(&GameTime::updateLoop, this).detach();
}

void GameTime::stop()
{
	running = false;
}

void GameTime::addObserver(ITimeObserver* observer) {
    observers.push_back(observer);
}

void GameTime::removeObserver(ITimeObserver* observer) {
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void GameTime::notifyObservers() {
    for (auto observer : observers) {
        observer->onTimeChanged();
    }
}

void GameTime::addSeconds(int realMinutes)
{
	int gameMinutes = static_cast<int>(realMinutes * timeSpeed);
	minute += gameMinutes;
	normalize();
	notifyObservers();  // 通知所有观察者时间已更新
}

std::string GameTime::toString() const
{
	std::string _time = std::to_string(year);
	_time += " ";
	_time += (month < 10) ? "0" + std::to_string(month) : std::to_string(month);
	_time += " ";
	_time += (day < 10) ? "0" + std::to_string(day) : std::to_string(day);
	_time += " ";
	switch (dayofweek){
		case 1:
			_time += "Mon";
			break;
		case 2:
			_time += "Tue";
			break;
		case 3:
			_time += "Wed";
			break;
		case 4:
			_time += "Thu";
			break;
		case 5:
			_time += "Fri";
			break;
		case 6:
			_time += "Sat";
			break;
		case 7:
			_time += "Sun";
			break;
	}
	_time += " ";
	_time += (hour < 10) ? "0" + std::to_string(hour) : std::to_string(hour);
	_time += ":";
	_time += (minute < 10) ? "0" + std::to_string(minute) : std::to_string(minute);
	_time += " ";
	return _time;
}

std::string GameTime::judgeTime()
{
	if (hour >= 6 && hour < 18) {
		return "day";
	}
	else if (hour>=18) {
		return "night";
	}
	else {
		return "midnight";
	}
}

void GameTime::setnextday()
{
	minute = 0;
	hour = 6;
	day++;
}