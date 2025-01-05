#ifndef _HOVER_BUTTON_H_
#define _HOVER_BUTTON_H_

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class HoverButton : public cocos2d::ui::Button 
{
public:
    // 创建一个新的 HoverButton 实例
    static HoverButton* create(const std::string& defaultButtonImage, const std::string& hoverButtonImage, const std::string& activeButtonImage);

    // 初始化 HoverButton 实例
    bool init(const std::string& defaultButtonImage, const std::string& hoverButtonImage, const std::string& activeButtonImage);

private:
    std::string defaultButtonImage; // 默认状态按钮图片路径
    std::string hoverButtonImage;   // 悬停状态按钮图片路径
    std::string activeButtonImage;  // 激活状态按钮图片路径

    // 鼠标移动事件的处理函数
    void onMouseMove(cocos2d::Event* event);

    // 鼠标释放事件的处理函数
    void onMouseUp(cocos2d::Event* event);
};

#endif // _HOVER_BUTTON_H_
