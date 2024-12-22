/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     InventoryLayer.cpp
 * File Function: InventoryLayer类的实现
 * Author:        张翔
 * Update Date:   2024/12/14
 ****************************************************************/

#include "InventoryLayer.h"
#include "proj.win32/Constant.h"

USING_NS_CC;

InventoryLayer::~InventoryLayer() {}

InventoryLayer* InventoryLayer::create()
{
    InventoryLayer* layer = new(std::nothrow) InventoryLayer();
    if (layer && layer->init()){
        layer->autorelease();
        return layer;
    }
    else {
        delete layer;
        return nullptr;
    }
}

bool InventoryLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    close();
    return true;
}

void InventoryLayer::close() 
{
    // 设置打开背包按钮
    auto InventoryButton = HoverButton::create("ImageElements/InventoryLayer/Slot.png",
        "ImageElements/InventoryLayer/Slot.png",
        "ImageElements/InventoryLayer/Slot.png");
    InventoryButton->setPosition(Vec2(Director::getInstance()->getWinSize().width - 100, 650) - Vec2(0, 100));
    InventoryButton->setContentSize(Size(50, 50));
    InventoryButton->setColor(ccc3(0, 128, 128));
    InventoryButton->addTouchEventListener([this, InventoryButton](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {

            open();
        }
        });

    auto MusicButton = HoverButton::create(slotpos, slotpos, slotpos);
    MusicButton->setPosition(InventoryButton->getPosition() - Vec2(0, 100));
    MusicButton->setContentSize(Size(50, 50));
    MusicButton->setColor(ccc3(0, 0, 128));
    MusicButton->addTouchEventListener([this, MusicButton](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
        {
            if (type == cocos2d::ui::Widget::TouchEventType::BEGAN)
            {
                if (g_backgroundMusicSign == DEFAULT_MUSIC_SIGN)
                {
                    audioPlayer(BackgroundMusic_Path, 1);
                }
                else
                {
                    audioPlayer_StopBackgroundMusic();
                }
            }
        });

    this->removeAllChildren();
    this->addChild(InventoryButton, 1, "InventoryButton");
    this->addChild(MusicButton, 1, "MusicButton");

    auto currentItemBackground = Sprite::create("ImageElements/InventoryLayer/Slot.png");
    currentItemBackground->setPosition(Vec2(100, 100));
    addChild(currentItemBackground, 1, "currentItemBackground");

    auto inventory = Inventory::getInstance();

    if (!inventory->getSlot(inventory->getCurrHeldItem()).isEmpty()) {
        auto currentItem = Sprite::create(inventory->getSlot(inventory->getCurrHeldItem()).getItem()->getImagePath());
        currentItem->setPosition(Vec2(100, 100));
        currentItem->setContentSize(Size(36, 36));
        addChild(currentItem, 2, "currentItem");
    }
}

void InventoryLayer::open()
{
    auto inventory = Inventory::getInstance();

    auto deleteInventoryButton = getChildByName("InventoryButton");
    if (deleteInventoryButton != nullptr){
        removeChild(deleteInventoryButton);
    }
    auto deleteMusicButton = getChildByName("MusicButton");
    if (deleteMusicButton != nullptr)
    {
        removeChild(deleteMusicButton);
    }
    auto deleteCurrentItem = getChildByName("currentItem");
    if (deleteCurrentItem != nullptr){
        removeChild(deleteCurrentItem);
    }
    auto deleteCurrentItemBackground = getChildByName("currentItemBackground");
    if (deleteCurrentItem != nullptr){
        removeChild(deleteCurrentItemBackground);
    }

    // 设置背景
    auto background = Sprite::create("ImageElements/InventoryLayer/InventoryLayerBackGround.png");
    background->setContentSize(Size(DESIGN_RESOLUTION_WIDTH - 100, DESIGN_RESOLUTION_HEIGHT - 100));
    background->setAnchorPoint(Vec2(0, 0));
    background->setPosition(Vec2(50, 50));
    background->setOpacity(128);
    this->addChild(background, 0, "background");

    // 设置格子
    for (int i = 0; i < DEFAULT_CAPACITY; i++){
        auto slotButton = HoverButton::create("ImageElements/InventoryLayer/Slot.png",
            "ImageElements/InventoryLayer/Slot.png",
            "ImageElements/InventoryLayer/Slot.png");
        slotButton->setPosition(Vec2(200, 400) + Vec2((i % 10) * 100, 0) - Vec2(0, (i / 10) * 100));
        slotButton->setContentSize(Size(50, 50));
        if(i == Inventory::getInstance()->getCurrHeldItem())
            slotButton->setColor(ccc3(0, 255, 0));
        slotButton->addTouchEventListener([this, i, slotButton](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
                if (type == cocos2d::ui::Widget::TouchEventType::BEGAN){
                    auto originalColor = slotButton->getColor();
                    this->getChildByName("slotButton" + std::to_string(Inventory::getInstance()->getCurrHeldItem()))->setColor(originalColor);
                    // 修改手持物品格子
                    Inventory::getInstance()->changeCurrHeldItem(i);

                    auto deleteCurrentItem = getChildByName("currentItem");
                    if (deleteCurrentItem != nullptr){
                        removeChild(deleteCurrentItem);
                    }
                    if (!Inventory::getInstance()->getSlot(Inventory::getInstance()->getCurrHeldItem()).isEmpty()){
                        auto currentItem = Sprite::create(Inventory::getInstance()->getSlot(Inventory::getInstance()->getCurrHeldItem()).getItem()->getImagePath());
                        currentItem->setPosition(Vec2(100, 100));
                        currentItem->setContentSize(Size(36, 36));
                        addChild(currentItem, 2, "currentItem");
                    }
                    slotButton->setColor(ccc3(0, 255, 0));
                }
            });
        this->addChild(slotButton, 1, "slotButton" + std::to_string(i));

        if (!Inventory::getInstance()->getSlot(i).isEmpty()) {
            auto itemIcon = Sprite::create(Inventory::getInstance()->getSlot(i).getItem()->getImagePath());
            itemIcon->setContentSize(Size(36, 36));
            itemIcon->setPosition(this->getChildByName("slotButton" + std::to_string(i))->getPosition());
            addChild(itemIcon, 2, "itemIcon" + std::to_string(i));

            auto itemNum = Label::create(std::to_string(Inventory::getInstance()->getSlot(i).getQuantity()), "", 30);
            itemNum->setColor(ccc3(0, 0, 0));
            itemNum->setPosition(itemIcon->getPosition() + Vec2(itemIcon->getBoundingBox().size.width / 2, 0 - itemIcon->getBoundingBox().size.height / 2));
            addChild(itemNum, 3, "itemNum");
        }
    }

    // 手持物品
    auto currentItemBackground = Sprite::create("ImageElements/InventoryLayer/Slot.png");
    currentItemBackground->setPosition(Vec2(100, 100));
    this->addChild(currentItemBackground, 1, "currentItemBackground");
    if (!Inventory::getInstance()->getSlot(Inventory::getInstance()->getCurrHeldItem()).isEmpty()) {
        auto currentItem = Sprite::create(Inventory::getInstance()->getSlot(Inventory::getInstance()->getCurrHeldItem()).getItem()->getImagePath());
        currentItem->setPosition(Vec2(100, 100));
        currentItem->setContentSize(Size(36, 36));
        this->addChild(currentItem, 2, "currentItem");
    }

    // 关闭按钮
    auto closeButton = HoverButton::create("ImageElements/InventoryLayer/CloseSlot.png",
        "ImageElements/InventoryLayer/CloseSlot.png", 
        "ImageElements/InventoryLayer/CloseSlot.png");
    closeButton->setPosition(Vec2(DESIGN_RESOLUTION_WIDTH - 100, 650));
    closeButton->setContentSize(Size(50, 50));
    closeButton->addTouchEventListener([this, closeButton](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN){
            close();
        }
        });
    this->addChild(closeButton, 1, "closeButton");

}