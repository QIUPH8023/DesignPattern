/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Manager.cpp
 * File Function: Manager类的实现
 * Author:        张翔
 * Update Date:   2024/12/19
 ****************************************************************/

#include "Manager.h"
#include "../Inventory/Inventory.h"
#include "../Item/Other.h"
#include "proj.win32/Json.hpp"
#include "fstream"

using json = nlohmann::json;

USING_NS_CC;

Manager* Manager::instance = nullptr;

Manager::Manager() :inYardScene(true) {}

Manager::~Manager()
{
    // 清理资源
    for (auto obj : objects) {
        delete obj;
    }
    for (auto land : lands) {
        delete land;
    }
    // 释放精灵
    farmlandSprites.clear();
    farmObjectSprites.clear();
}

Manager* Manager::getInstance()
{
    if (instance == nullptr) {
        instance = new(std::nothrow)Manager();
        instance->init();
        if (!instance) {
            CC_SAFE_DELETE(instance);
        }
    }
    return instance;
}

void Manager::init(const std::string& filename)
{
    // 用存档(默认初始地图)初始化
    this->loadGameState(filename);

}

void Manager::setScene(bool scene)
{
    inYardScene = scene;
}

size_t Manager::getLandsSize()
{
    return lands.size();
}

FarmLand* Manager::getland(int index)
{
    return lands[index];
}

size_t Manager::getObjectsSize()
{
    return objects.size();
}

FarmObject* Manager::getObject(int index)
{
    return objects[index];
}

void Manager::addFarmland(float x, float y, Scene* scene)
{
    FarmLand* newland = new (std::nothrow)FarmLand(x, y);
    lands.push_back(newland);
    auto newlandSprite = Sprite::create("ImageElements/FarmLands/DrySoil.png");
    if (newlandSprite) {
        // 根据耕地的 x, y 坐标设置精灵的位置
        newlandSprite->setPosition(newland->getX(), newland->getY());
        newlandSprite->setAnchorPoint(Vec2(0, 0));
        newlandSprite->setCameraMask(unsigned short(CameraFlag::USER1));
        // 将精灵添加到场景中
        scene->addChild(newlandSprite, 0);
        // 保存精灵到容器中
        farmlandSprites.push_back(newlandSprite);
    }
}

void Manager::addObject(ObjectType type, float x, float y, Scene* scene)
{
    try {
        // 创建新的农场对象
        FarmObject* newobj = new (std::nothrow) FarmObject(type, x, y);
        if (!newobj) {
            CCLOG("Failed to allocate memory for new FarmObject");
            return;
        }

        objects.push_back(newobj);

        Sprite* newobjSprite = nullptr;

        // 根据对象类型选择对应的纹理
        switch (newobj->getObjectType()) {
        case TREE:
            newobjSprite = Sprite::create("ImageElements/FarmObjects/Tree1State_1.png");
            newobjSprite->setAnchorPoint(Vec2(0.5, 0));
            break;
        case WEED:
            newobjSprite = Sprite::create("ImageElements/FarmObjects/WeedState_1.png");
            newobjSprite->setAnchorPoint(Vec2(0, 0));
            break;
        case STONE:
            newobjSprite = Sprite::create("ImageElements/FarmObjects/StoneState_1.png");
            newobjSprite->setAnchorPoint(Vec2(0, 0));
            break;
        case RADISH:
            newobjSprite = Sprite::create("ImageElements/FarmObjects/RadishState_1.png");
            newobjSprite->setAnchorPoint(Vec2(0, 0));
            break;
        case POTATO:
            newobjSprite = Sprite::create("ImageElements/FarmObjects/PotatoState_1.png");
            newobjSprite->setAnchorPoint(Vec2(0, 0));
            break;
        case WHEAT:
            newobjSprite = Sprite::create("ImageElements/FarmObjects/WheatState_1.png");
            newobjSprite->setAnchorPoint(Vec2(0, 0));
            break;
        default:
            CCLOG("Unknown object type: %d", newobj->getObjectType());
            break;
        }

        // 如果成功创建了精灵
        if (newobjSprite) {
            newobjSprite->setPosition(newobj->getX(), newobj->getY());
            newobjSprite->setCameraMask(static_cast<unsigned short>(CameraFlag::USER1));
            scene->addChild(newobjSprite, 1);
            farmObjectSprites.push_back(newobjSprite);
        }
        else {
            CCLOG("Failed to create sprite for object type: %d", newobj->getObjectType());
        }
    }
    catch (const std::exception& e) {
        // 捕获并处理标准异常
        CCLOG("Exception caught in addObject: %s", e.what());
    }
    catch (...) {
        // 捕获未知异常
        CCLOG("Unknown exception caught in addObject");
    }
}

void Manager::addToScene(Scene* scene)
{
    auto manager = Manager::getInstance();
    manager->setScene(true);
    // 添加农田到场景
    for (size_t i = 0; i < manager->getLandsSize(); i++) {
        auto land = manager->getland(i);
        if (land) {
            manager->addFarmland(land->getX(), land->getY(), scene);
        }
        else {
            CCLOG("Null pointer detected in lands at index %zu", i);
        }
    }
    // 添加对象到场景
    for (size_t i = 0; i < manager->getObjectsSize(); i++) {
        auto obj = manager->getObject(i);
        if (obj) {
            manager->addObject(obj->getObjectType(), obj->getX(), obj->getY(), scene);
        }
        else {
            CCLOG("Null pointer detected in objects at index %zu", i);
        }
    }
}

void Manager::removeFromScene()
{
    inYardScene = false;
    farmlandSprites.clear();
    farmObjectSprites.clear();
}

void Manager::harvestObject(float x, float y, Scene* scene)
{
    auto obj = findObjectByPosition(x, y);
    obj->markForRemoval();
    auto inventory = Inventory::getInstance();
    switch (obj->getObjectType()) {
    case TREE:
        inventory->addItem(ITEM_OTHER_FOOD_APPLE, 1);
        inventory->addItem(ITEM_OTHER_MATERIAL_WOOD, 5);
        break;
    case WEED:
        inventory->addItem(ITEM_OTHER_MATERIAL_GRASS, 5);
        break;
    case STONE:
        inventory->addItem(ITEM_OTHER_MATERIAL_STONE, 5);
        break;
    case RADISH:
        inventory->addItem(ITEM_OTHER_CROP_RADISH, 5);
        break;
    case POTATO:
        inventory->addItem(ITEM_OTHER_CROP_POTATO, 5);
        break;
    case WHEAT:
        inventory->addItem(ITEM_OTHER_CROP_WHEAT, 5);
        break;
    default:
        break;
    }
}

FarmLand* Manager::findFarmlandByPosition(float x, float y)
{
    // 遍历所有耕地精灵
    for (size_t i = 0; i < farmlandSprites.size(); i++) {
        auto& sprite = farmlandSprites[i];
        // 获取精灵的位置
        auto pos = sprite->getPosition();
        // 使用 Vec2::distance 来计算两点之间的距离
        if (Vec2(pos.x, pos.y).distance(Vec2(x, y)) < 0.01f) {  
            // 返回对应的 FarmLand 对象
            return lands[i];  
        }
    }
    // 如果没有找到匹配的精灵，返回 nullptr
    return nullptr;
}

FarmObject* Manager::findObjectByPosition(float x, float y)
{
    // 遍历所有非耕地精灵
    for (size_t i = 0; i < farmObjectSprites.size(); i++) {
        auto& sprite = farmObjectSprites[i];
        // 获取精灵的位置
        auto pos = sprite->getPosition();
        // 使用 Vec2::distance 来计算两点之间的距离
        if (Vec2(pos.x, pos.y).distance(Vec2(x, y)) < 0.01f) {  
            // 返回对应的 FarmObject 对象
            return objects[i];  
        }
    }
    // 如果没有找到匹配的精灵，返回 nullptr
    return nullptr;  
}

void Manager::update()
{
    // 更新耕地
    for (size_t i = 0; i < farmlandSprites.size(); i++) {
        if (lands[i]->shouldRemove()) {
            lands.erase(lands.begin() + i);
            if (inYardScene) {
                farmlandSprites[i]->getParent()->removeChild(farmlandSprites[i]);
            }
            continue;
        }
        auto statebefore = lands[i]->getLandState();
        lands[i]->update();
        if (statebefore != lands[i]->getLandState() && inYardScene) {
            if(lands[i]->getLandState()==DRY)
                farmlandSprites[i]->setTexture("ImageElements/FarmObjects/DrySoil.png");
            else if(lands[i]->getLandState() == WET)
                farmlandSprites[i]->setTexture("ImageElements/FarmObjects/WetSoil.png");
        }
    }

    // 更新非耕地实体
    for (size_t i = 0; i < farmObjectSprites.size(); i++) {
        if (findFarmlandByPosition(objects[i]->getX(), objects[i]->getY()) == nullptr) {
            objects.erase(objects.begin() + i);
            if (inYardScene) {
                farmObjectSprites[i]->getParent()->removeChild(farmObjectSprites[i]);
            }
            continue;
        }
        auto statebefore = objects[i]->getCurrState();
        objects[i]->update();
        if (statebefore != objects[i]->getCurrState() && inYardScene) {
            if (objects[i]->getObjectType() == RADISH)
                farmObjectSprites[i]->setTexture(OBJECT_RADISH_STATE[objects[i]->getCurrState()]);
            else if (objects[i]->getObjectType() == POTATO)
                farmObjectSprites[i]->setTexture(OBJECT_POTATO_STATE[objects[i]->getCurrState()]);
            else if (objects[i]->getObjectType() == WHEAT)
                farmObjectSprites[i]->setTexture(OBJECT_WHEAT_STATE[objects[i]->getCurrState()]);
        }
    }
}

bool Manager::isPointInAnyObject(float x, float y)
{
    for (auto obj : objects) {
        // 获取每个对象的边界框
        Rect rect = obj->getSize();
        if (rect.containsPoint(cocos2d::Vec2(x, y))){
            // 如果点在某个对象的边界框内
            return true;  
        }
    }
    return false;
}

void Manager::saveGameState(const std::string& filename)
{
    json gameState;

    // 保存 FarmLand 数据
    json landsArray;
    for (auto land : lands) {
        json landData;
        landData["x"] = land->getX();  
        landData["y"] = land->getY();
        landData["state"] = static_cast<int>(land->getLandState()); 
        landsArray.push_back(landData);
    }
    gameState["lands"] = landsArray;

    // 保存 FarmObject 数据
    json objectsArray;
    for (auto object : objects) {
        json objectData;
        objectData["x"] = object->getX();
        objectData["y"] = object->getY();
        objectData["type"] = static_cast<int>(object->getObjectType()); 
        objectData["state"] = static_cast<int>(object->getCurrState());
        objectsArray.push_back(objectData);
    }
    gameState["objects"] = objectsArray;

    // 保存为 JSON 文件
    std::ofstream outFile(filename);
    outFile << gameState.dump(4);
    outFile.close();
}

void Manager::loadGameState(const std::string& filename) 
{
    std::ifstream inFile(filename);
    if (!inFile) {
        // 文件不存在，直接返回
        return;  
    }

    // 读取文件内容
    json gameState;
    try {
        // 尝试解析 JSON 文件内容
        inFile >> gameState;  
    }
    catch (const json::parse_error& e) {
        // 捕捉 JSON 解析错误，防止程序崩溃
        CCLOG("JSON 解析错误: %s", e.what());
        return;
    }

    // 检查 JSON 是否为空
    if (gameState.is_null()) {
        CCLOG("游戏数据为空！");
        return;
    }

    // 加载 FarmLand 数据
    if (gameState.contains("lands")) {
        const auto& landsArray = gameState["lands"];
        for (const auto& landData : landsArray) {
            FarmLand* land = new FarmLand(
                landData["x"].get<float>(),
                landData["y"].get<float>()
            );
            land->setLandState(static_cast<LandState>(landData["state"].get<int>()));  // 设置状态
            lands.push_back(land);
        }
    }

    // 加载 FarmObject 数据
    if (gameState.contains("objects")) {
        const auto& objectsArray = gameState["objects"];
        for (const auto& objectData : objectsArray) {
            ObjectType type = static_cast<ObjectType>(objectData["type"].get<int>());
            FarmObject* object = new FarmObject(type, objectData["x"].get<float>(), objectData["y"].get<float>());
            object->setCurrState(objectData["state"].get<int>());
            objects.push_back(object);
        }
    }
}
