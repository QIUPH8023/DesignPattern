/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     ChatLayer.cpp
 * File Function: ChatLayer类的实现
 * Author:        刘逸飞
 * Update Date:   2024/12/16
 ****************************************************************/

#include "ChatLayer.h"
#include "ShopLayer.h"

USING_NS_CC;

ChatLayer::ChatLayer() : currentNPC(nullptr), isStoreOpen(false) {}

ChatLayer::~ChatLayer() {}

bool ChatLayer::init(NPC* npc)
{
    if (!Layer::init()) {
        return false;
    }

    currentNPC = npc;

    // 创建menu
    auto menu = Menu::create();
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu, 0, "menu");

    // 创建对话按钮(点击推进对话)
    auto chatButton = MenuItemImage::create("ImageElements/ChatLayer/ChatLayerBackGround.png", 
        "ImageElements/ChatLayer/ChatLayerBackGround.png", 
        CC_CALLBACK_1(ChatLayer::chatButtonCallBack, this));
    chatButton->setScale(0.3);
    chatButton->setPosition(Vec2(DESIGN_RESOLUTION_WIDTH - chatButton->getBoundingBox().size.width / 2, 3 * chatButton->getBoundingBox().size.height));
    menu->addChild(chatButton,1,"chatButton");
    // 对话按钮的文本
    auto chatButtonContent = Label::createWithTTF("闲谈", "Fonts/FangZhengZhaoGeYuan.ttf", 30);
    chatButtonContent->setPosition(chatButton->getPosition());
    chatButtonContent->setColor(Color3B(0, 0, 0));
    this->addChild(chatButtonContent,10, "chatButtonContent");

    // 创建事件按钮(点击后弹出 买卖东西，制作物品 的界面)
    auto eventButton = MenuItemImage::create("ImageElements/ChatLayer/ChatLayerBackGround.png", 
        "ImageElements/ChatLayer/ChatLayerBackGround.png", 
        CC_CALLBACK_1(ChatLayer::eventButtonCallBack, this));
    eventButton->setScale(0.3);
    eventButton->setPosition(Vec2(DESIGN_RESOLUTION_WIDTH - eventButton->getBoundingBox().size.width / 2, 2 * eventButton->getBoundingBox().size.height));
    menu->addChild(eventButton,10,"eventButton");
    // 事件按钮的文本
    auto eventButtonContent = Label::createWithTTF("事件", "Fonts/FangZhengZhaoGeYuan.ttf", 30);
    eventButtonContent->setPosition(eventButton->getPosition());
    eventButtonContent->setColor(Color3B(0, 0, 0));
    this->addChild(eventButtonContent, 10, "eventButtonContent");

    // 创建关闭按钮(退出对话)
    auto quitButton = MenuItemImage::create("ImageElements/ChatLayer/ChatLayerBackGround.png",
        "ImageElements/ChatLayer/ChatLayerBackGround.png",
        CC_CALLBACK_1(ChatLayer::quitButtonCallBack, this));
    quitButton->setScale(0.3);
    quitButton->setPosition(Vec2(DESIGN_RESOLUTION_WIDTH - quitButton->getBoundingBox().size.width / 2, quitButton->getBoundingBox().size.height));
    menu->addChild(quitButton,10,"quitButton");
    // 关闭按钮的文本
    auto quitButtonContent = Label::createWithTTF("退出", "Fonts/FangZhengZhaoGeYuan.ttf", 30);
    quitButtonContent->setPosition(quitButton->getPosition());
    quitButtonContent->setColor(Color3B(0, 0, 0));
    this->addChild(quitButtonContent, 10, "quitButtonContent");

    // 创建人物头像
    auto profileHead = Sprite::create(currentNPC->getHead());
    profileHead->setContentSize(Size(3 * quitButton->getBoundingBox().size.height, 3 * quitButton->getBoundingBox().size.height));
    profileHead->setAnchorPoint(Vec2(0, 0));
    profileHead->setPosition(Vec2(0,quitButton->getBoundingBox().size.height / 2));
    this->addChild(profileHead, 10, "profileHead");

    // 创建对话框背景
    auto background = Sprite::create("ImageElements/ChatLayer/ChatLayerBackGround.png");
    background->setContentSize(Size(DESIGN_RESOLUTION_WIDTH - quitButton->getBoundingBox().size.width- profileHead->getBoundingBox().size.width, 3 * quitButton->getBoundingBox().size.height));
    background->setAnchorPoint(Vec2(1, 0));
    background->setPosition(Vec2(DESIGN_RESOLUTION_WIDTH - quitButton->getBoundingBox().size.width, quitButton->getBoundingBox().size.height / 2));
    this->addChild(background, 0, "background");

    // 创建对话文本标签
    std::string contents = currentNPC->getDialog();
    auto content = Label::createWithTTF("你好啊！", "Fonts/FangZhengZhaoGeYuan.ttf", 30);
    content->setAnchorPoint(Vec2(0, 1));
    content->setAlignment(TextHAlignment::LEFT, TextVAlignment::TOP);
    content->setPosition(Vec2(profileHead->getContentSize().width + 10, background->getContentSize().height + quitButton->getBoundingBox().size.height / 2 - 60));
    content->setColor(Color3B(0,0,0));
    this->addChild(content, 10, "content");
    
    // 创建人物姓名 好感度显示
    auto name = Label::create(" " + currentNPC->getNPCName() + " (好感度 :" + currentNPC->getNPCLikability() + ")", "", 30);
    name->setColor(Color3B(0, 0, 0));
    name->setAnchorPoint(Vec2(0, 0));
    name->setPosition(content->getPosition());
    this->addChild(name, 10, "name");

    // 设置layer属性
    setColor(Color3B(0, 0, 0));
    setOpacity(128);

    return true;
}

ChatLayer* ChatLayer::create(NPC* npc)
{
    ChatLayer* layer = new(std::nothrow) ChatLayer();
    if (layer && layer->init(npc)) {
        layer->autorelease();
        return layer;
    }
    else {
        delete layer;
        return nullptr;
    }
}

void ChatLayer::updateDialog()
{
    currentNPC->advanceDialog();
    auto content1 = dynamic_cast<Label*>(this->getChildByName("content"));
    content1->setString(currentNPC->getDialog());
}

void ChatLayer::closeChat()
{
    currentNPC->jumpToDialog(0);
    this->removeFromParentAndCleanup(true);
}

void ChatLayer::chatButtonCallBack(Ref* pSender)
{
    updateDialog();
    currentNPC->setNPCLove(1);
}

void ChatLayer::eventButtonCallBack(Ref* pSender)
{
    // 如果事件窗口未打开
    if (!isStoreOpen) {
        isStoreOpen = 1;
        Size winSize = Director::getInstance()->getWinSize();

        // 打开购买/制作界面
        auto storebackground = Sprite::create("ImageElements/ChatLayer/ChatLayerBackGround.png");
        storebackground->setContentSize(Size(winSize.width, winSize.height - 3.5 * this->getChildByName("menu")->getChildByName("quitButton")->getBoundingBox().size.height));
        storebackground->setAnchorPoint(Vec2(0, 0));
        storebackground->setPosition(Vec2(0, 3.5 * this->getChildByName("menu")->getChildByName("quitButton")->getBoundingBox().size.height));
        storebackground->setOpacity(128);
        this->addChild(storebackground, 0, "storebackground");

        // 更改事件文本
        auto content1 = dynamic_cast<Label*>(this->getChildByName("eventButtonContent"));
        content1->setString("退出商店");

        // 打开商店
        auto shop = ShopLayer::create();
        shop->setNPC(currentNPC);
        switch (currentNPC->getNPCType()) {
            case ALEX:
                shop->InsertShopItems(ITEM_OTHER_CROP_RADISH, 1, SHOP_SELL);
                shop->InsertShopItems(ITEM_OTHER_CROP_POTATO, 1, SHOP_SELL);
                shop->InsertShopItems(ITEM_OTHER_CROP_WHEAT , 1, SHOP_SELL);

                shop->InsertShopItems(ITEM_OTHER_FOOD_APPLE, 10, SHOP_BUY);

                shop->InsertShopItems(ITEM_OTHER_CROP_POTATO, 1, TASK_PAID);
                shop->InsertShopItems(ITEM_OTHER_FOOD_FRIED_POTATO, 1, TASK_REWARD);

                break;
            case ABIGAIL:
                shop->InsertShopItems(ITEM_SEED_RADISH_SEED, 10, SHOP_BUY);
                shop->InsertShopItems(ITEM_SEED_POTATO_SEED, 10, SHOP_BUY);
                shop->InsertShopItems(ITEM_SEED_WHEAT_SEED, 10, SHOP_BUY);
                shop->InsertShopItems(ITEM_OTHER_PRESENT_FLOWER, 10, SHOP_BUY);

                shop->InsertShopItems(ITEM_OTHER_PRESENT_FLOWER, 1, TASK_PAID);
                
                break;
            case CAROLINE:
                shop->InsertShopItems(ITEM_TOOL_HOE, 1, SHOP_BUY);
                shop->InsertShopItems(ITEM_TOOL_WATERING_CAN, 1, SHOP_BUY);
                shop->InsertShopItems(ITEM_TOOL_PICKAXE, 1, SHOP_BUY);
                shop->InsertShopItems(ITEM_TOOL_AXE, 1, SHOP_BUY);
                shop->InsertShopItems(ITEM_TOOL_SCYTHE, 1, SHOP_BUY);
                shop->InsertShopItems(ITEM_TOOL_FISHING_ROD, 1, SHOP_BUY);

                shop->InsertShopItems(ITEM_OTHER_MATERIAL_STONE, 1, TASK_PAID);
                shop->InsertShopItems(ITEM_TOOL_PICKAXE, 1, TASK_REWARD);
                shop->InsertShopItems(ITEM_TOOL_AXE, 1, TASK_REWARD);

                break;
            case LEWIS:
                shop->InsertShopItems(ITEM_OTHER_MATERIAL_WOOD, 10, SHOP_BUY);
                shop->InsertShopItems(ITEM_OTHER_MATERIAL_STONE, 10, SHOP_BUY);
                shop->InsertShopItems(ITEM_OTHER_MATERIAL_GRASS, 10, SHOP_BUY);

                shop->InsertShopItems(ITEM_OTHER_CROP_RADISH, 1, SHOP_SELL);
                shop->InsertShopItems(ITEM_OTHER_CROP_POTATO, 1, SHOP_SELL);
                shop->InsertShopItems(ITEM_OTHER_CROP_WHEAT, 1, SHOP_SELL);

                shop->InsertShopItems(ITEM_SEED_RADISH_SEED, 1, TASK_REWARD);
                shop->InsertShopItems(ITEM_SEED_POTATO_SEED, 1, TASK_REWARD);
                shop->InsertShopItems(ITEM_SEED_WHEAT_SEED, 1, TASK_REWARD);

                break;
        }
        shop->UpdateShopItems();
        this->addChild(shop, 3,"shop");
    }
    else  {
        isStoreOpen = false;
        // 关闭购买/制作界面
        this->removeChildByName("storebackground");
        auto shop = dynamic_cast<ShopLayer*>(this->getChildByName("shop"));
        shop->DeleteShop();
        this->removeChildByName("shop");
        // 更改事件文本
        auto content1 = dynamic_cast<Label*>(this->getChildByName("eventButtonContent"));
        content1->setString("事件");
    }
}
void ChatLayer::quitButtonCallBack(Ref* pSender)
{
    closeChat();
}

