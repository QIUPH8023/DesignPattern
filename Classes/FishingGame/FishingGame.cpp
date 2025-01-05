#include "FishingGame.h"

USING_NS_CC;

FishingGame* FishingGame::create()
{
    FishingGame* ret = new FishingGame();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

bool FishingGame::init()
{
    if (!Layer::init()) {
        return false;
    }
    // 设置背景
    fishingBar = Sprite::create("ImageElements/FishingLayer/FishingBar.png");
    fishingBar->setAnchorPoint(Vec2(0.5, 0.5));
    fishingBar->setPosition(Vec2(DESIGN_RESOLUTION_WIDTH / 2, DESIGN_RESOLUTION_HEIGHT / 2));
    this->addChild(fishingBar, 0, "fishingBar");

    // 设置钓鱼条
    auto fishingPos = Sprite::create("ImageElements/FishingLayer/Close.png");
    fishingPos->setColor(Color3B(0, 0, 255));
    fishingPos->setContentSize(Size(fishingPos->getContentSize().width, fishingPos->getContentSize().height - 30));
    fishingPos->setPosition(fishingBar->getPosition());
    this->addChild(fishingPos, 1, "fishingPos");

    // 设置鱼竿位置
    fishingRod = Sprite::create("ImageElements/FishingLayer/FishingRod.png");
    fishingRod->setContentSize(Size(fishingRod->getContentSize().width, fishingPos->getContentSize().height));
    fishingRod->setPosition(Vec2(fishingBar->getPosition().x-0.3 * fishingBar->getContentSize().width, fishingBar->getPosition().y));
    this->addChild(fishingRod, 2, "fishingRod");

    // 创建背景
    auto menu = Menu::create();
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu, 0, "menu");

    // 设置钓鱼按钮
    auto fishingButton = HoverButton::create("ImageElements/FishingLayer/FishingButton.png",
        "ImageElements/FishingLayer/FishingButton.png",
        "ImageElements/FishingLayer/FishingButton.png");
    fishingButton->setPosition(Vec2(DESIGN_RESOLUTION_WIDTH / 2, DESIGN_RESOLUTION_HEIGHT / 2 + FISHING_LAYER_FISHING_BUTTON_OFFSET_Y));
    fishingButton->addTouchEventListener([this](Ref* sender, cocos2d::ui::Widget::TouchEventType type) mutable {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            auto moveAction = MoveBy::create(0.3f, Vec2(20, 0));
            this->getChildByName("fishingRod")->runAction(moveAction);

            //fishingRod->setPosition(fishingRod->getPosition() + Vec2(10, 0));
        }
        });
    this->addChild(fishingButton, 0, "fishingButton");

    auto fishingButtonContent = Label::createWithTTF("快速按下按钮实现钓鱼!!!", "Fonts/FangZhengZhaoGeYuan.ttf", 40);
    fishingButtonContent->setColor(Color3B(255, 0, 0));
    fishingButtonContent->setPosition(fishingButton->getPosition() + Vec2(300,0));
    fishingButtonContent->setRotation(30);
    this->addChild(fishingButtonContent, 1, "fishingButtonContent");

    // 设置进度条
    auto loadingBar = ui::LoadingBar::create("ImageElements/FishingLayer/Close.png");
    loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
    loadingBar->setPosition(fishingBar->getPosition() - Vec2(0, fishingBar->getContentSize().height) / 2  + Vec2(0,25));
    loadingBar->setScaleX(2.6);
    loadingBar->setScaleY(0.2);
    loadingBar->setColor(Color3B(0, 255, 255));
    loadingBar->setPercent(1);
    this->addChild(loadingBar, 2, "loadingBar");

    // 设置剩余时间显示
    auto lasttime = Label::createWithTTF("还剩下: " + std::to_string(fishingTime) + "秒!!!", "Fonts/FangZhengZhaoGeYuan.ttf", 40);
    lasttime->setAnchorPoint(Vec2(0, 0.5));
    lasttime->setRotation(-10);
    lasttime->setPosition(fishingButton->getPosition() - Vec2(fishingBar->getContentSize().width / 2, 0));
    lasttime->setColor(Color3B(0, 0, 0));
    this->addChild(lasttime, 3, "lasttime");

    return true;
}

void FishingGame::fishingEnd() 
{
    this->removeFromParentAndCleanup(true);
}

bool FishingGame::fishingUpdate(float delta)
{
    // 获取页面内的一些元素
    auto fishrod = this->getChildByName("fishingRod");
    auto fishbar = this->getChildByName("fishingBar");
    auto fishpos = this->getChildByName("fishingPos");
    auto loadbar = this->getChildByName("loadingBar");

    if (fishingTime <= 0) {
        _fishCaught = 0;
        return true;
    }
    else if (dynamic_cast<ui::LoadingBar*>(loadbar)->getPercent() >= 100) {
        _fishCaught = 1;
        return true;
    }
    else{
        fishingTime--;
        auto lasttime = dynamic_cast<Label*>(this->getChildByName("lasttime"));
        lasttime->setString("剩余时间: " + std::to_string(fishingTime) + "秒");
        if (fishrod->getPosition().x >= fishbar->getPosition().x - fishbar->getContentSize().width / 2){
            auto moveAction = MoveBy::create(1.0f, Vec2(-60, 0));
            this->getChildByName("fishingRod")->runAction(moveAction);
            
        }
        if (fishrod->getPosition().x <= fishpos->getPosition().x + fishpos->getContentSize().width / 2 && 
            fishrod->getPosition().x >= fishpos->getPosition().x - fishpos->getContentSize().width / 2){
            auto newpercent = dynamic_cast<ui::LoadingBar*>(loadbar)->getPercent();
            dynamic_cast<ui::LoadingBar*>(loadbar)->setPercent(newpercent + 10);
        }
    }
    return false;
}

bool FishingGame::FishingResult()
{
    fishingEnd();
    return _fishCaught;
}

bool FishingGame::FishingGameStart()
{
    schedule([this](float delta){
        if (Update(delta)) {
            unschedule("fishing_update_key");
            fishingEnd();
            if (_fishCaught) {
                Inventory::getInstance()->addItem(std::shared_ptr<Item>(ITEM_OTHER_FOOD_FISH), 1);
            }
        }
        }, 1.0f, "fishing_update_key");
    return true;
}

bool FishingGame::Update(float delta)
{
    if (fishingUpdate(delta)) {
        return true;
    }
    return false;
}

FishingGame::FishingGame() : fishingTime(20), _fishCaught(false) {}

FishingGame::~FishingGame() {}
