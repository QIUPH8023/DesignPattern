/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Manager.h
 * File Function: Manager类的定义
 * Author:        张翔
 * Update Date:   2024/12/19
 ****************************************************************/

#ifndef _MANAGER_
#define _MANAGER_

#include "vector"
#include "cocos2d.h"
#include "FarmObject.h"
#include "FarmLand.h"

class Manager
{
public:
    // 获取单例指针
	static Manager* getInstance();

     // 禁止拷贝和赋值
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;

    // 析构函数
    ~Manager();

    // 初始化
    void init(const std::string& filename = "Archive/ManagerDefaultArchive.json");

    // 添加对象
    void addObject(ObjectType type, float x, float y, cocos2d::Scene* scene);

    // 是否切换场景
    void setScene(bool scene);

    void addToScene(cocos2d::Scene* scene);

    // 退出农场场景时执行
    void removeFromScene();

    // 收获对象
    void harvestObject(float x, float y, cocos2d::Scene* scene);

    // 添加耕地
    void addFarmland(float x, float y, cocos2d::Scene* scene);

    // 根据坐标查找耕地
    FarmLand* findFarmlandByPosition(float x, float y);

    // 根据坐标查找非耕地对象
    FarmObject* findObjectByPosition(float x, float y);

    // 判断某一点是否在对象的碰撞面积内
    bool isPointInAnyObject(float x, float y);

    // 保存游戏状态
    void saveGameState(const std::string& filename);

    // 加载游戏数据
    void loadGameState(const std::string& filename);

    // 更新方法
    void update();

    // 获取耕地数量
    size_t getLandsSize();

    // 获取物体数量
    size_t getObjectsSize();

    // 获得某一块耕地
    FarmLand* getland(int index);

    // 获取某一个对象
    FarmObject* getObject(int index);

private:
    std::vector<FarmLand*> lands;                       // 耕地物体
    std::vector<FarmObject*> objects;                   // 非耕地物体
    std::vector<cocos2d::Sprite*> farmlandSprites;      // 耕地物体对应精灵
    std::vector<cocos2d::Sprite*> farmObjectSprites;    // 非耕地物体对应精灵
    bool inYardScene;                                   // 是否在农场场景

    // 私有构造函数
    Manager();

    // 静态单例指针
    static Manager* instance;

};

#endif // _MANAGER_
