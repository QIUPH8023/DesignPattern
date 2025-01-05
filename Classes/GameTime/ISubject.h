#ifndef _I_SUBJECT_H_
#define _I_SUBJECT_H_

#include "ITimeObserver.h"

/***************************************************************
 * 类名称: ISubject
 * 功能描述: 抽象主题接口，定义了观察者模式中被观察者应该具有的方法
 * 作者: 张翔
 ***************************************************************/
class ISubject {
public:
    virtual ~ISubject() = default;

    // 添加观察者
    virtual void addObserver(ITimeObserver* observer) = 0;

    // 移除观察者
    virtual void removeObserver(ITimeObserver* observer) = 0;

    // 通知所有观察者状态发生改变
    virtual void notifyObservers() = 0;
};

#endif // _I_SUBJECT_H_
