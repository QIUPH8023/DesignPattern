#ifndef _I_TIME_OBSERVER_H_
#define _I_TIME_OBSERVER_H_

/***************************************************************
 * 类名称: ITimeObserver
 * 功能描述: 抽象观察者接口，定义了响应时间变化的更新接口
 * 作者: 张翔
 ***************************************************************/
class ITimeObserver {
public:
    virtual ~ITimeObserver() = default;

    // 当被观察的时间发生变化时调用此方法
    virtual void onTimeChanged() = 0;
};

#endif // _I_TIME_OBSERVER_H_
