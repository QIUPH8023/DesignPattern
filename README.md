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

         C++11 引入了 `auto` 和 `decltype` 关键字，其允许编译器自动推导变量或表达式的类型，方便开发者编码也简化了代码。
      
        `auto` ：让编译器在编译器就推导出变量的类型，可以通过 `=` 右边的类型推导出变量的类型。

        `decltype` ：相对于 `auto` 用于推导变量类型，而 `decltype` 则用于推导表达式类型，这里只用于编译器分析表达式的类型，表达式实际不会进行运算。

        本项目在复杂数据类型时使用了 `auto` 和 `decltype` 方便创建变量以面对复杂的类型表达式，同时减少由于类型错误造成的 bug，也提高了维护性。

        使用举例如下:

        

  * [X] 空指针关键字 `nullptr`
 
        C++11 引入了 `nullptr` 关键字，它是一个表示空指针的字面量，用于替代传统 C++ 中的 `NULL` 。在之前的 C++ 标准中， `NULL` 通常被定义为 `0` 或 `((void*)0)` ，这可能导致类型歧义和一些难以发现的错误。

  * [X] 修饰常量 `constexpr`
 
        `constexpr` 是 C++11 新引入的关键字，用于编译时的常量和常量函数。 `constexpr` 修饰的才是真正的常量，它会在编译期间就会被计算出来，整个运行过程中都不可以被改变， `constexpr` 可以用于修饰函数，这个函数的返回值会尽可能在编译期间被计算出来当作一个常量，但是如果编译期间此函数不能被计算出来，那它就会当作一个普通函数被处理。

        使用举例如下：

```cpp
constexpr int DESIGN_RESOLUTION_WIDTH = 1280;
constexpr int DESIGN_RESOLUTION_HEIGHT = 720;
```
 
  * [x] `lambda` 表达式
 
        `lambda` 表达式是 C++11 最重要也最常用的一个特性之一。它能够就地匿名定义目标函数或函数对象，不需要额外写一个命名函数或者函数对象。以更直接的方式去写程序，好的可读性和可维护性。
 
  * [X] 时间库 `chrono` 和线程库 `this_thread`

        C++11 引入了 `chrono` 库，用于处理时间。这个库提供了时间点（time points）和持续时间（durations）的表示，以及时钟（clocks）。

        C++11 标准引入了线程库，它提供了对线程的控制和管理。在这里， `std::this_thread` 是一个命名空间，它提供了与当前线程相关的函数。特别地， `std::this_thread::sleep_for` 是一个函数，用于使当前线程休眠指定的时间。

        本项目中实现 `GameTime` 类的基本思路就是创建一个新线程从而保证游戏时间的独立更新。

  * [X] 基于范围的 `for` 循环

        C++11 引入了基于范围的 `for` 循环（Range-based for loop），这是一种新的循环语法，使得遍历容器（如数组、向量、列表等）和范围变得更加简单和直观。这种循环方式自动迭代容器或范围中的每个元素，无需手动管理迭代器或索引。
        
  * [X] 合理地抛出异常和处理

        `Try-Catch` 是一种异常处理机制，用于在程序中捕获和处理可能发生的异常或错误。在使用 `Try-Catch` 结构时，代码块被放置在一个 `Try` 块中，该块用于包含可能会抛出异常的代码。如果在 `Try` 块中发生异常，程序会立即跳转到对应的 `Catch` 块，这样就可以执行特定的异常处理代码，而不会导致程序崩溃。

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

- 实现 `InventoryLayer` 类
- 实现 `FarmLand` 类
- 实现 `FarmObject` 类
- 实现 `Manager` 类
- 实现 `FishingGame` 类
- 在 `Manager` 类中补充实现存档功能
- 在 `Inventory` 类中补充实现存档功能

### 2024/12/22

- 完善人物的交互功能
- 完善测试游戏功能，美化界面
- 完善项目说明文档
- 制作答辩PPT
