/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Manager.cpp
 * File Function: Manager类的实现
 * Author:        张翔
 * Update Date:   2024/12/19
 ****************************************************************/

#include "Manager.h"
#include "proj.win32/Json.hpp"
#include "fstream"

using json = nlohmann::json;

USING_NS_CC;

Manager* Manager::instance = nullptr;

Manager::Manager() {}

Manager::~Manager() 
{
    for (auto obj : objects) {
        delete obj;
    }
    for (auto land : lands) {
        delete land;
    }
}

Manager* Manager::getInstance()
{
    if (instance == nullptr) {
        instance = new(std::nothrow)Manager();
        if (!instance || !instance->init()) {
            delete instance; 
            instance = nullptr; 
            return nullptr;
        }
    }
	return instance;
}

bool Manager::init()
{
    
    return true;
}

void Manager::addToScene(Scene* scene)
{
    for (auto& land : lands) {
        auto sprite = land->getSprite(); 
        if (sprite && !land->isAddedToScene) {
            scene->addChild(sprite, 1);
            land->isAddedToScene = true; 
        }
    }
    for (auto& obj : objects) {
        auto sprite = obj->getSprite(); 
        if (sprite && !obj->isAddedToScene) {
            scene->addChild(sprite, 2);
            obj->isAddedToScene = true;  
        }
    }
}

void Manager::removeFromScene(Scene* scene)
{
    for (auto& land : lands) {
        auto sprite = land->getSprite(); 
        if (sprite && land->isAddedToScene) {
            scene->removeChild(sprite);
            land->isAddedToScene = false;
        }
    }
    for (auto& obj : objects) {
        auto sprite = obj->getSprite();
        if (sprite && obj->isAddedToScene) {
            scene->removeChild(sprite);
            obj->isAddedToScene = false;
        }
    }
}

void Manager::addObject(ObjectType type,float x,float y, Scene* scene)
{
    FarmObject* newobj = new(std::nothrow) FarmObject(type, x, y);
    objects.push_back(newobj);
    if (newobj->getSprite()) {
        scene->addChild(newobj->getSprite());
    }
}

void Manager::addFarmland(float x,float y, Scene* scene)
{
    FarmLand* newland = new (std::nothrow)FarmLand(x, y);
    lands.push_back(newland);
    if (newland->getSprite()) {
        scene->addChild(newland->getSprite());
    }
}

FarmLand* Manager::findFarmlandByPosition(float x, float y)
{
    for (auto& land : lands) {
        // 检查耕地的中心坐标是否匹配
        auto pos = land->getSprite()->getPosition();
        if (std::abs(pos.x - x) < 0.01 && std::abs(pos.y - y) < 0.01) {
            return land;
        }
    }
    return nullptr; 
}

FarmObject* Manager::findObjectByPosition(float x, float y)
{
    for (auto& obj : objects) {
        // 检查对象的中心坐标是否匹配
        auto pos = obj->getSprite()->getPosition();
        if (std::abs(pos.x - x) < 0.01 && std::abs(pos.y - y) < 0.01) {
            return obj;
        }
    }
    return nullptr; 
}

void Manager::update(Scene* scene)
{
    // 更新耕地
    for (auto it = lands.begin(); it != lands.end(); ) {
        FarmLand* land = *it;
        if (!land) {
            it = lands.erase(it);
            continue;
        }
        if (land->shouldRemove()) {
            if (land->getSprite() && land->isAddedToScene) {
                scene->removeChild(land->getSprite());
            }
            delete land; // 删除指针
            it = lands.erase(it);
        }
        else {
            land->update();
            ++it;
        }
    }

    // 更新非耕地实体
    for (auto it = objects.begin(); it != objects.end(); ) {
        FarmObject* obj = *it;
        if (!obj) {
            it = objects.erase(it);
            continue;
        }
        if (obj->shouldRemove()) {
            if (obj->getSprite() && obj->isAddedToScene) {
                scene->removeChild(obj->getSprite());
            }
            delete obj; // 删除指针
            it = objects.erase(it);
        }
        else {
            obj->update();
            ++it;
        }
    }
}

void Manager::saveGameState(const std::string& filename)
{
    json gameData;

    // 保存耕地数据
    json landsData = json::array();
    for (const auto* land : lands) {
        if (!land || !land->getSprite()) continue;
        json landJson;
        landJson["x"] = land->getSprite()->getPositionX();
        landJson["y"] = land->getSprite()->getPositionY();
        landJson["state"] = static_cast<int>(land->getLandState());
        landsData.push_back(landJson);
    }
    gameData["lands"] = landsData;

    // 保存非耕地对象数据
    json objectsData = json::array();
    for (const auto* obj : objects) {
        if (!obj || !obj->getSprite()) continue;
        json objJson;
        objJson["x"] = obj->getSprite()->getPositionX();
        objJson["y"] = obj->getSprite()->getPositionY();
        objJson["type"] = static_cast<int>(obj->getObjectType());
        objJson["currstate"] = obj->getCurrState();
        objectsData.push_back(objJson);
    }
    gameData["objects"] = objectsData;

    std::ofstream file(filename);
    if (file.is_open()) {
        file << gameData.dump(4);
        file.close();
    }
}

void Manager::loadGameState(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        CCLOG("无法打开文件: %s", filename.c_str());
        return;
    }

    json gameData;
    file >> gameData;
    file.close();

    // 清空当前数据并释放内存
    for (auto* land : lands) delete land;
    for (auto* obj : objects) delete obj;
    lands.clear();
    objects.clear();

    // 加载耕地数据
    for (const auto& landJson : gameData["lands"]) {
        float x = landJson["x"];
        float y = landJson["y"];
        LandState state = static_cast<LandState>(landJson["state"]);
        auto* land = new FarmLand(x, y);
        land->setLandState(state);
        lands.push_back(land);
    }

    // 加载非耕地对象数据
    for (const auto& objJson : gameData["objects"]) {
        float x = objJson["x"];
        float y = objJson["y"];
        ObjectType type = static_cast<ObjectType>(objJson["type"]);
        int currstate = objJson["currstate"];
        auto* obj = new FarmObject(type, x, y);
        obj->setCurrState(currstate);
        objects.push_back(obj);
    }
}
