#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

 /*
  * Class Name:     AppDelegate
  * Class Function: Cocos2d-x 应用程序类
  */
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    // 析构函数
    virtual ~AppDelegate();

    // 初始化 OpenGL 上下文属性
    virtual void initGLContextAttrs();

    // 当应用程序完成启动并准备进入主循环时调用此函数
    virtual bool applicationDidFinishLaunching();

    // 当应用程序进入后台时调用此函数
    virtual void applicationDidEnterBackground();

    // 当应用程序从后台返回到前台时调用此函数
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

