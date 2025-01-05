/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     ShopLayer.cpp
 * File Function: ShopLayer类的实现
 * Author:        刘逸飞
 * Update Date:   2024/12/16
 ****************************************************************/
#include "ShopLayer.h"

USING_NS_CC;

ShopLayer::ShopLayer() {}

ShopLayer* ShopLayer::create()
{
    ShopLayer* layer = new(std::nothrow) ShopLayer();
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    else {
        delete layer;
        return nullptr;
    }
}

// 初始化
bool ShopLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    // 初始化商店状态
    isOpen = false;
    shopStatusLabel = nullptr;

    // 注册为时间观察者
    GameTime::getInstance()->addObserver(this);

    // 初始检查营业状态
    setShopStatus(checkBusinessHours());

    return true;
}

void ShopLayer::onTimeChanged()
{
    setShopStatus(checkBusinessHours());
}

bool ShopLayer::checkBusinessHours()
{
    std::string timeStr = GameTime::getInstance()->toString();
    int hour = std::stoi(timeStr.substr(11,2));

    // 营业时间 9:00-17:00
    return (hour >= 9 && hour < 17);
}

void ShopLayer::setShopStatus(bool open)
{
    isOpen = open;

    // 移除旧的状态标签
    if (shopStatusLabel) {
        this->removeChild(shopStatusLabel);
        shopStatusLabel = nullptr;
    }

    // 创建新的状态标签
    std::string statusText = isOpen ? "营业中" : "休息中";
    shopStatusLabel = cocos2d::Label::createWithTTF(statusText, "Fonts/FangZhengZhaoGeYuan.ttf", 30);
    shopStatusLabel->setPosition(cocos2d::Vec2(400, 500));
    shopStatusLabel->setColor(isOpen ? cocos2d::Color3B(0, 255, 0) : cocos2d::Color3B(255, 0, 0));
    this->addChild(shopStatusLabel, 10);

    // 更新所有交易按钮状态
    auto buttons = this->getChildren();
    for (auto& child : buttons) {
        auto button = dynamic_cast<cocos2d::ui::Button*>(child);
        if (button) {
            button->setEnabled(isOpen);
        }
    }
}

// 设置对话/交易/委托/赠送的NPC
void ShopLayer::setNPC(NPC* npc)
{
    _currentNPC = npc;
}

// 获取背包物品所在格子
Slot& ShopLayer::getInventorySlots(std::shared_ptr<Item> item)
{
    return Inventory::getInstance()->getSlot(Inventory::getInstance()->findItem(item));
}

// 进行交易 失去_PaidItems 得到_ShopItems 返回交易是否成功
bool ShopLayer::tradeItems()
{
    if (!isOpen) {
        // 显示提示信息
        auto closedTip = cocos2d::Label::createWithTTF("商店休息中，无法交易",
            "Fonts/FangZhengZhaoGeYuan.ttf", 30);
        closedTip->setPosition(cocos2d::Vec2(400, 300));
        closedTip->setColor(cocos2d::Color3B(255, 0, 0));
        this->addChild(closedTip, 10);

        // 2秒后自动移除提示
        auto removeAction = cocos2d::Sequence::create(
            cocos2d::DelayTime::create(2.0f),
            cocos2d::CallFunc::create([closedTip]() {
                closedTip->removeFromParent();
            }),
            nullptr
        );
        closedTip->runAction(removeAction);

        return false;
    }

    // 检查背包中是否有委托物品
    for (int i = 0; i < _ShopItems.size(); i++) {
        // 定位委托物品
        if (_ShopItemsType[i] == TASK_PAID) {
            auto paid = _ShopItems[i];
            if (Inventory::getInstance()->findItem(paid) == -1)
            {
                return false;
            }
        }
    }
    // 删除委托物品
    for (int i = 0; i < _ShopItems.size(); i++) {
        // 定位委托物品
        if (_ShopItemsType[i] == TASK_PAID) {
            auto paid = _ShopItems[i];
            if (Inventory::getInstance()->findItem(paid) != -1) {
                // 从背包中取出对应paid物品
                getInventorySlots(std::shared_ptr<Item>(paid)).changeQuantity(_ShopItemsNum[i]);
                continue;
            }
        }
    }
    // 向背包添加奖励
    for (int i = 0; i < _ShopItems.size(); i++) {
        // 定位奖励
        if (_ShopItemsType[i] == TASK_REWARD) {
            // 添加奖励
            Inventory::getInstance()->addItem(std::shared_ptr<Item>(_ShopItems[i]), _ShopItemsNum[i]);
        }
    }

    return true;
}

// 更新商店内物品及其显示
void ShopLayer::UpdateShopItems()
{
    Size winSize = Director::getInstance()->getWinSize();

    // 菜单界面 放置购买/交付委托/赠送礼物的button

    // 设置剩余金钱数量显示
    auto bullet = Label::createWithTTF(std::to_string(Inventory::getInstance()->getCoin()), "Fonts/FangZhengZhaoGeYuan.ttf", 30);
    bullet->setPosition(Vec2(40, 20));
    bullet->setColor(Color3B(0, 0, 0));
    this->addChild(bullet, 3);

    // 显示商店内已有物品
    for (int i = 0; i < _ShopItems.size(); i++) {
        if (_ShopItemsType[i] == SHOP_BUY || _ShopItemsType[i] == SHOP_SELL) {
            // 添加物品图标
            auto item = _ShopItems[i];
            auto itemIcon = Sprite::create(item->getImagePath());
            itemIcon->setContentSize(Size(36, 36));
            itemIcon->setPosition(Vec2(50, winSize.height - 80) + Vec2(60, 0) - i * Vec2(0, 60));
            this->addChild(itemIcon, 1, enumToString(item->getType()));

            // 添加购买按钮 金钱->物品
            auto itemButton = HoverButton::create("hoverBox.png",
                "hoverBox.png",
                "hoverBox.png");
            itemButton->setPosition(itemIcon->getPosition() - Vec2(40, 0));
            itemButton->setContentSize(Size(10, 10));

            Label* itemName;

            switch (_ShopItemsType[i]) {
            case SHOP_BUY:
                itemName = Label::createWithTTF(enumToString(item->getType()) + " 购买 $" + std::to_string(item->getprice()) + " 剩余 *" + std::to_string(_ShopItemsNum[i]),  "Fonts/FangZhengZhaoGeYuan.ttf", 30);
                itemButton->addTouchEventListener([this, i, bullet, itemButton, itemName, item](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
                    if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
                        if (!Inventory::getInstance()->isSlotFull() || Inventory::getInstance()->isCoinEnough(_ShopItems[i]->getprice()) || _ShopItemsNum[i] != 0) {
                            if (Inventory::getInstance()->getCoin() > _ShopItems[i]->getprice()) {
                                Inventory::getInstance()->changeCoin(0 - _ShopItems[i]->getprice());
                                Inventory::getInstance()->addItem(std::shared_ptr<Item>(_ShopItems[i]), 1);
                                _ShopItemsNum[i]--;
                                bullet->setString(std::to_string(Inventory::getInstance()->getCoin()));
                                itemName->setString(enumToString(item->getType()) + " 购买 $" + std::to_string(item->getprice()) + " 剩余 *" + std::to_string(_ShopItemsNum[i]));
                            }
                            else {
                                itemButton->setColor(ccc3(255, 0, 0));
                            }
                        }
                    }
                    });

                break;
            case SHOP_SELL:
                itemName = Label::createWithTTF(enumToString(item->getType()) + " 出售 $" + std::to_string(item->getprice()), "Fonts/FangZhengZhaoGeYuan.ttf", 30);
                itemButton->addTouchEventListener([this, i, bullet](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
                    if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
                        if (Inventory::getInstance()->findItem(std::shared_ptr<Item>(_ShopItems[i])) != -1) {
                            Inventory::getInstance()->getSlot(Inventory::getInstance()->findItem(std::shared_ptr<Item>(_ShopItems[i]))).changeQuantity(1);
                            Inventory::getInstance()->changeCoin(_ShopItems[i]->getprice());
                            bullet->setString(std::to_string(Inventory::getInstance()->getCoin()));
                        }
                    }
                    });

                break;
            }

            this->addChild(itemButton, 2);

            // 添加物品类型
            itemName->setAnchorPoint(Vec2(0, 0.5));
            itemName->setPosition(itemIcon->getPosition() + Vec2(itemIcon->getContentSize().width, 0));
            itemName->setColor(Color3B(0, 0, 0));
            this->addChild(itemName, 1);

            // 添加物品描述
            auto itemDescription = Label::createWithTTF(item->getDescription(), "Fonts/FangZhengZhaoGeYuan.ttf", 30);
            itemDescription->setAnchorPoint(Vec2(0, 0.5));
            itemDescription->setPosition(itemName->getPosition() + Vec2(0, itemName->getContentSize().height));
            itemDescription->setColor(Color3B(0, 0, 0));
            this->addChild(itemDescription, 1);
        }
    }

    // 显示委托
    {
        // 添加交付按钮
        auto TaskButton = HoverButton::create("hoverBox.png",
            "hoverBox.png",
            "hoverBox.png");
        TaskButton->setPosition(Vec2(110, 300));
        TaskButton->setContentSize(Size(10, 10));
        // 委托内容显示
        std::string rewardstr = " ";
        std::string paidstr = " ";
        for (int i = 0; i < _ShopItems.size(); i++) {
            if (_ShopItemsType[i] == TASK_PAID) {
                auto a = _ShopItems[i];
                _ShopItems[i]->getType();
                paidstr += enumToString(_ShopItems[i]->getType()) + "*" + std::to_string(_ShopItemsNum[i]) + " ";
            }
            else if (_ShopItemsType[i] == TASK_REWARD)
                rewardstr += enumToString(_ShopItems[i]->getType()) + "*" + std::to_string(_ShopItemsNum[i]) + " ";
        }
        auto TaskRewardLabel = Label::createWithTTF("任务回报:" + rewardstr, "Fonts/FangZhengZhaoGeYuan.ttf", 30);
        TaskRewardLabel->setAnchorPoint(Vec2(0, 0.5));
        TaskRewardLabel->setPosition(TaskButton->getPosition() + Vec2(36, 0));
        TaskRewardLabel->setColor(Color3B(0, 0, 0));
        addChild(TaskRewardLabel, 2, "TaskRewardLabel");

        auto TaskPaidLabel = Label::createWithTTF("委托需求:" + paidstr, "Fonts/FangZhengZhaoGeYuan.ttf", 30);
        TaskPaidLabel->setAnchorPoint(Vec2(0, 0.5));
        TaskPaidLabel->setPosition(TaskButton->getPosition() + Vec2(36, -30));
        TaskPaidLabel->setColor(Color3B(0, 0, 0));
        addChild(TaskPaidLabel, 2, "TaskPaidLabel");

        TaskButton->addTouchEventListener([this, TaskButton](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
            if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
                // 如果交付成功
                if (tradeItems() == 1) {
                    auto TaskFinishLabel = Label::createWithTTF("已完成", "Fonts/FangZhengZhaoGeYuan.ttf", 30);
                    TaskFinishLabel->setPosition(TaskButton->getPosition());
                    TaskFinishLabel->setColor(Color3B(255, 0, 0));
                    addChild(TaskFinishLabel, 3, "TaskFinishLabel");
                    TaskButton->setEnabled(false);
                }
            }
            });
        addChild(TaskButton, 2, "TaskButton");
    }
}

// 向商店中_ShopItems添加物品
void ShopLayer::InsertShopItems(std::shared_ptr<Item> _item, int num, ShopType type)
{
    for (int i = 0; i < _ShopItems.size(); i++) {
        // 已有相同操作类型的物品
        if (_ShopItems[i] == _item && _ShopItemsType[i] == type) {
            _ShopItemsNum[i] += num;
            return;
        }
    }

    _ShopItems.push_back(_item);
    _ShopItemsNum.push_back(num);
    _ShopItemsType.push_back(type);
}

void ShopLayer::DeleteShop()
{
    this->removeAllChildren();
}

ShopLayer::~ShopLayer()
{
    // 在析构时移除观察者
    GameTime::getInstance()->removeObserver(this);
}