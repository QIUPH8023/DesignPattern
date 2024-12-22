## Stardew_Valley_Farm

2024同济大学程序设计范式期末大作业

## 项目名称

Stardew_Valley_Farm

## 项目简介

该项目是一个基于 [cocos2d-x 3.17.2](https://docs.cocos.com/cocos2d-x/manual/) 开发的星露谷农村游戏。
该游戏是一个农场生活模拟游戏，玩家将管理自己的农场。

## 成员分工

|姓名|学号|分工|
| :----:| :----: | :----: |
|张翔(组长)|2352985|项目任务分工 <br> 代码审查 <br> 项目框架搭建 <br> `AppDelegate` 类 <br> `Player` 类<br>`HoverButton` 类<br> `AudioPlayr`类<br>`NPC`类<br>`MenuScene`类<br>`SaveLoadScnen`类|
|刘逸飞|2353935| |



## 成员贡献

|姓名|学号|代码量|工作量|
| :----:| :----: | :----: | :----: |
|张翔(组长)|2352985||
|刘逸飞|2353935| ||

## 项目组成

* `/Classes`
类定义与类实现

* `/Resources`
资源文件

* `/proj.win32`
游戏程序

## 项目实现功能与项目技术细节

### 实现功能

* [X] 有初始界面和设置界面
* [X] 支持背景音效和交互音效
* [X] 支持人物的自由移动、物体碰撞和摄像机跟随
* [X] 有多张游戏地图，支持场景自由切换
* [X] 支持多种农场活动，包括砍树、挖矿、耕田、种地、钓鱼
* [X] 有多种NPC，支持与NPC对话、购买商品、完成委托
* [X] 支持存档功能 

### 加分项

* 版本控制
  
  * [X] 合理使用 Git 控制版本，将项目开源至 Github

        Github 项目托管 [仓库](https://github.com/Muoow/Stardew_Valley_Farm)

  * [X]  组员分工合理，积极交流
 
        按照每个组员的擅长点分配合适的项目功能，提高项目完成效率

* 尽可能多地使用了 C++11 特性

  * [X] 类型推导

         

  * [X] 空指针关键字 `nullptr`

  * [X] 修饰常量 `constexpr`
 
  * [x] `lambda` 表达式
 
  * [X] 时间库 `chrono` 和线程库 `this_thread`

  * [X] 基于范围的 `for` 循环

* 实现了简易的存档功能

  * [X] 自主学习了适用于现代C++的Josn文件编辑器 Github[地址](https://github.com/nlohmann/json)

* 代码规范性强

  * [X] 组内代码风格相似

        组长在正式开始项目制作之前就规范了代码的基础风格，包括换行、注释等

        组长对组员的每次提交之前都进行的检查和规范

  * [X] 代码质量高

         

## 项目开发日志

### 2024/11/23

- Python 环境配置
- Cmake 环境配置
- cocos2d-x 4.0 环境配置
  
### 2024/11/24

- 放弃cocos2d-x 4.0，转而使用cocos2d-x 3.17.2

### 2024/11/27

- 学习cocos2d-x
  
### 2024/12/3

- 明确分工和代码规范性
- 实现 `MenuScene` 类

### 2024/12/5

- 实现 `Player` 类

### 2024/12/6

- 补充 `Player` 类中移动动画的实现
- 开始实现 `FarmYardScene` 类中的物体碰撞

### 2024/12/10

- 基本实现物体碰撞功能
- 基本实现 `FarmYardScene` 类中的鼠标交互功能
- 实现 `AudioEngine` 类

### 2024/12/14

- 初步实现 `Item` 类
- 实现 `Tool`类
- 实现 `Seed`类

### 2024/12/15

- 实现 `GameTime` 类
- 实现 `Inventory` 类

### 2024/12/16

- 初步实现 `ChatLayer` 类

### 2024/12/18

- 实现 `FarmHouse` 类
- 实现 `TownCenter` 类
- 实现人物场景切换
- 初步实现钓鱼小游戏

### 2024/12/19

- 实现 `GameTimeLayer`类
- 实现 `Slot`类
- 实现 `Inventory`类

### 2024/12/21

- 实现 `InventoryLayer`类
- 实现 `FarmLand`类
- 实现 `FarmObject`类
- 实现 `Manager`类
- 在`Inventory`类中补充实现存档功能

### 2024/12/22

- 完善人物的交互功能
- 完善测试游戏功能，美化界面
- 完善项目说明文档
- 制作答辩PPT
