/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     SaveLoadScene.h
 * File Function: SaveLoadScene类的实现
 * Author:        张翔
 * Update Date:   2024/12/22
 ****************************************************************/

#include "SaveLoadScene.h"
#include "MenuScene.h"
#include "../Button/HoverButton.h"
#include "proj.win32/Constant.h"

USING_NS_CC;

Scene* SaveLoadScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SaveLoadScene::create();
    scene->addChild(layer);
    return scene;
}

bool SaveLoadScene::init()
{
    // 创建场景
    if (!Scene::init()) {
        return false;
    }

    // 加载背景
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("Scenes/SaveLoadScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建按钮
    auto ArchiveButton1 = HoverButton::create("Buttons/SaveLoadSceneButtons/ArchiveDefaultButton_1.png",
        "Buttons/SaveLoadSceneButtons/ArchiveDefaultButton_1.png",
        "Buttons/SaveLoadSceneButtons/ArchiveDefaultButton_1.png");
    auto ArchiveButton2 = HoverButton::create("Buttons/SaveLoadSceneButtons/ArchiveDefaultButton_2.png",
        "Buttons/SaveLoadSceneButtons/ArchiveDefaultButton_2.png",
        "Buttons/SaveLoadSceneButtons/ArchiveDefaultButton_2.png");
    auto ArchiveButton3 = HoverButton::create("Buttons/SaveLoadSceneButtons/ArchiveDefaultButton_3.png",
        "Buttons/SaveLoadSceneButtons/ArchiveDefaultButton_3.png",
        "Buttons/SaveLoadSceneButtons/ArchiveDefaultButton_3.png");

    // 设置按钮位置
    ArchiveButton1->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + SAVELOAD_SCENE_ARCHIVE_BUTTON_1_OFFSET_Y));
    ArchiveButton2->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + SAVELOAD_SCENE_ARCHIVE_BUTTON_2_OFFSET_Y));
    ArchiveButton3->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + SAVELOAD_SCENE_ARCHIVE_BUTTON_3_OFFSET_Y));

    // 为按钮添加事件处理器
    ArchiveButton1->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {



        }
        });

    ArchiveButton2->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {



        }
        });

    ArchiveButton3->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {



        }
        });

    auto BackButton = HoverButton::create("Buttons/SaveLoadSceneButtons/BackDefaultButton.png",
        "Buttons/SaveLoadSceneButtons/BackHoverButton.png",
        "Buttons/SaveLoadSceneButtons/BackHoverButton.png");

    BackButton->setPosition(Vec2(SAVELOAD_SCENE_BACK_BUTTON_X, SAVELOAD_SCENE_BACK_BUTTON_Y));

    BackButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {


            Director::getInstance()->popScene();
        }
        });

    // 将按钮加入场景
    this->addChild(ArchiveButton1);
    this->addChild(ArchiveButton2);
    this->addChild(ArchiveButton3);
    this->addChild(BackButton);

    return true;

}