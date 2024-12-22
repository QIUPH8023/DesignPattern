/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     MenuScene.h
 * File Function: MenuScene类的实现
 * Author:        张翔
 * Update Date:   2024/12/3
 ****************************************************************/
#include "MenuScene.h"
#include "SaveLoadScene.h"
#include "../Button/HoverButton.h"
#include "../Map/FarmYardScene.h"
#include "../Music/AudioPlayer.h"
#include "../GameTime/GameTime.h"
#include "../Manager/Manager.h"
#include "../Inventory/Inventory.h"
#include "proj.win32/Constant.h"

USING_NS_CC;

// 创建场景
Scene* MenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}

// 初始化场景
bool MenuScene::init()
{
    // 创建场景
    if (!Scene::init()) {
        return false;
    }

    // 加载背景
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("Scenes/MenuScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    audioPlayer(BACK_GOUND_MUSIC_PATH, 1);
    // 创建按钮
    auto newGameButton = HoverButton::create("Buttons/MenuSceneButtons/CreateDefualtButton.png",
        "Buttons/MenuSceneButtons/CreateHoverButton.png",
        "Buttons/MenuSceneButtons/CreateHoverButton.png");
    auto loadGameButton = HoverButton::create("Buttons/MenuSceneButtons/LoadDefaultButton.png",
        "Buttons/MenuSceneButtons/LoadHoverButton.png",
        "Buttons/MenuSceneButtons/LoadHoverButton.png");
    auto exitGameButton = HoverButton::create("Buttons/MenuSceneButtons/ExitDefaultButton.png",
        "Buttons/MenuSceneButtons/ExitHoverButton.png",
        "Buttons/MenuSceneButtons/ExitHoverButton.png");

    // 设置按钮位置
    newGameButton->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_NEW_GAME_BUTTON_OFFSET_X, screenSize.height / 2 + MENU_SCENE_BUTTONS_OFFSET_Y));
    loadGameButton->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_LOAD_GAME_BUTTON_OFFSET_X, screenSize.height / 2 + MENU_SCENE_BUTTONS_OFFSET_Y));
    exitGameButton->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_EXIT_GAME_BUTTON_OFFSET_X, screenSize.height / 2 + MENU_SCENE_BUTTONS_OFFSET_Y));

    // 为按钮添加事件处理器
    newGameButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            audioPlayer(CLICK_SOUND_EFFECT_PATH);
            // 加载新游戏
            GameTime::getInstance()->start();
            Manager::getInstance()->loadGameState("Archive/ManagerDefaultArchive.json");
            Inventory::getInstance()->loadInventoryState("Archive/InventoryArchive.json");
            Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, FarmYardScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });

    loadGameButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            audioPlayer(CLICK_SOUND_EFFECT_PATH);
            // 进入读档界面
            Director::getInstance()->pushScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, SaveLoadScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });

    exitGameButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            audioPlayer(CLICK_SOUND_EFFECT_PATH);
            // 退出游戏
            Director::getInstance()->end();
        }
        });

    // 将按钮加入场景
    this->addChild(newGameButton);
    this->addChild(loadGameButton);
    this->addChild(exitGameButton);

    return true;
}

