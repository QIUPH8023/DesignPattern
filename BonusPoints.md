### 加分项

* 版本控制
  
  * [X] 合理使用 Git 控制版本，将项目开源至 Github

        Github 项目托管 [仓库] (https://github.com/Muoow/Stardew_Valley_Farm)

  * [X]  组员分工合理，积极交流
 
        按照每个组员的擅长点分配合适的项目功能，提高项目完成效率

* 尽可能多地使用了 C++11 特性

  * [X] 类型推导

         C++11 引入了 `auto` 和 `decltype` 关键字，其允许编译器自动推导变量或表达式的类型，方便开发者编码也简化了代码。
      
        `auto` ：让编译器在编译器就推导出变量的类型，可以通过 `=` 右边的类型推导出变量的类型。

        `decltype` ：相对于 `auto` 用于推导变量类型，而 `decltype` 则用于推导表达式类型，这里只用于编译器分析表达式的类型，表达式实际不会进行运算。

        本项目在复杂数据类型时使用了 `auto` 和 `decltype` 方便创建变量以面对复杂的类型表达式，同时减少由于类型错误造成的 bug，也提高了维护性。

        使用举例如下:

        ```cpp
        // 获取 FarmYard 地图对象
        auto FarmYard = (TMXTiledMap*)this->getChildByName("FarmYard");
	      auto Manager = Manager::getInstance();
	      auto targetpos = targettile->getPosition();
        ```

  * [X] 空指针关键字 `nullptr`
 
        C++11 引入了 `nullptr` 关键字，它是一个表示空指针的字面量，用于替代传统 C++ 中的 `NULL` 。在之前的 C++ 标准中， `NULL` 通常被定义为 `0` 或 `((void*)0)` ，这可能导致类型歧义和一些难以发现的错误。

        使用举例如下:

        ```cpp
        // 如果没有找到匹配的精灵，返回 nullptr
        return nullptr;
        ```

  * [X] 修饰常量 `constexpr`
 
        `constexpr` 是 C++11 新引入的关键字，用于编译时的常量和常量函数。 `constexpr` 修饰的才是真正的常量，它会在编译期间就会被计算出来，整个运行过程中都不可以被改变， `constexpr` 可以用于修饰函数，这个函数的返回值会尽可能在编译期间被计算出来当作一个常量，但是如果编译期间此函数不能被计算出来，那它就会当作一个普通函数被处理。

        使用举例如下：

        ```cpp
        constexpr int DESIGN_RESOLUTION_WIDTH = 1280;
        constexpr int DESIGN_RESOLUTION_HEIGHT = 720;
        ```
 
  * [x] `lambda` 表达式
 
        `lambda` 表达式是 C++11 最重要也最常用的一个特性之一。它能够就地匿名定义目标函数或函数对象，不需要额外写一个命名函数或者函数对象。以更直接的方式去写程序，好的可读性和可维护性。

        使用举例如下：

        ```cpp
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
        ```

  * [X] 时间库 `chrono` 和线程库 `this_thread`

        C++11 引入了 `chrono` 库，用于处理时间。这个库提供了时间点（time points）和持续时间（durations）的表示，以及时钟（clocks）。

        C++11 标准引入了线程库，它提供了对线程的控制和管理。在这里， `std::this_thread` 是一个命名空间，它提供了与当前线程相关的函数。特别地， `std::this_thread::sleep_for` 是一个函数，用于使当前线程休眠指定的时间。

        本项目中实现 `GameTime` 类的基本思路就是创建一个新线程从而保证游戏时间的独立更新。
        
        使用举例如下：

        ```cpp
        void GameTime::updateLoop()
        {
          	while (running) {
		        // 更新间隔
		        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		        // 添加时间
		        addSeconds(1); 
	          }
        }
        ```
        
  * [X] 基于范围的 `for` 循环

        C++11 引入了基于范围的 `for` 循环（Range-based for loop），这是一种新的循环语法，使得遍历容器（如数组、向量、列表等）和范围变得更加简单和直观。这种循环方式自动迭代容器或范围中的每个元素，无需手动管理迭代器或索引。
        
  * [X] 合理地抛出异常和处理

        `Try-Catch` 是一种异常处理机制，用于在程序中捕获和处理可能发生的异常或错误。在使用 `Try-Catch` 结构时，代码块被放置在一个 `Try` 块中，该块用于包含可能会抛出异常的代码。如果在 `Try` 块中发生异常，程序会立即跳转到对应的 `Catch` 块，这样就可以执行特定的异常处理代码，而不会导致程序崩溃。

        使用举例如下:

        ```cpp
        json jsonData;
        try {
	          file >> jsonData;
        }
        catch (const json::parse_error& e) {
          	CCLOG("Error parsing JSON");
          	file.close();
          	return;
        }
        ```

  * [X] 智能指针 `shared_ptr`和`unique_ptr`

        `shared_ptr` 和 `unique_ptr` 是 C++ 标准库中的两个智能指针类型，用于自动管理动态分配的内存，防止内存泄漏。

        ```cpp
        // 物品类型
        const std::shared_ptr<Other> ITEM_OTHER_FOOD_APPLE = std::make_shared<Other>(FOOD_APPLE, "Items/FOOD_APPLE.png", 200, 1);
        const std::shared_ptr<Other> ITEM_OTHER_FOOD_BREAD = std::make_shared<Other>(FOOD_BREAD, "Items/FOOD_BREAD.png", 200, 1);
        const std::shared_ptr<Other> ITEM_OTHER_FOOD_FRIED_POTATO = std::make_shared<Other>(FOOD_FRIED_POTATO, "Items/FOOD_FRIED_POTATO.png", 200, 1);
        ```

* 实现了简易的存档功能

  * [X] 自主学习了适用于现代 C++ 的Josn文件编辑器 原仓库 Github [地址](https://github.com/nlohmann/json)
 
  * [X] 引用 `Json.hpp` 头文件，实现了向指定文件内读入/写入数据，进而实现了简单的存档功能

* 代码质量高、规范性强

  * [X] 组内代码风格相似

        组长在正式开始项目制作之前就规范了代码的基础风格，包括换行、注释等

        组长对组员的每次提交之前都进行了仔细检查和规范

  * [X] 常变量的集中定义

        本项目的 `Constant.h` 头文件集中存放了所有常变量的定义，方便直接在程序中取用

