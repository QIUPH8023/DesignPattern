/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Constant.h
 * File Function: 常变量的定义
 * Author:        张翔
 * Update Date:   2024/12/11
 ****************************************************************/

#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include "vector"
#include <string>

constexpr int DESIGN_RESOLUTION_WIDTH = 1280;												 // 设计分辨率宽度
constexpr int DESIGN_RESOLUTION_HEIGHT = 720;												 // 设计分辨率高度
constexpr int SMALL_RESOLUTION_WIDTH = 960;													 // 小分辨率宽度
constexpr int SMALL_RESOLUTION_HEIGHT = 540;											     // 小分辨率高度
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;                                                // 中分辨率宽度
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;                                                // 中分辨率高度
constexpr int LARGE_RESOLUTION_WIDTH = 1920;                                                 // 大分辨率宽度
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;                                                // 大分辨率高度
constexpr float FRAME_RATE = 60.0f;                                                          // 应用程序帧率
const std::string APPLICATION_TITLE = "星露谷物语 Stardew Valley";                           // 应用程序标题

constexpr float SCENE_TRANSITION_DURATION = 0.3f;                                            // 场景转换时长

constexpr int MENU_SCENE_BUTTONS_OFFSET_Y = -200;                                            // 菜单界面按钮Y轴偏移量
constexpr int MENU_SCENE_NEW_GAME_BUTTON_OFFSET_X = -400;                                    // 菜单界面开始按钮X轴偏移量
constexpr int MENU_SCENE_LOAD_GAME_BUTTON_OFFSET_X = 0;                                      // 菜单界面载入按钮X轴偏移量
constexpr int MENU_SCENE_EXIT_GAME_BUTTON_OFFSET_X = 400;                                    // 菜单界面结束按钮X轴偏移量

constexpr int SAVELOAD_SCENE_ARCHIVE_BUTTON_1_OFFSET_Y = 200;                                // 存档界面存档1按钮Y轴偏移量
constexpr int SAVELOAD_SCENE_ARCHIVE_BUTTON_2_OFFSET_Y = 20;                                 // 存档界面存档2按钮Y轴偏移量
constexpr int SAVELOAD_SCENE_ARCHIVE_BUTTON_3_OFFSET_Y = -160;                               // 存档界面存档3按钮Y轴偏移量
constexpr int SAVELOAD_SCENE_BACK_BUTTON_X = 150;                                            // 存档界面返回按钮X轴坐标
constexpr int SAVELOAD_SCENE_BACK_BUTTON_Y = 60;                                             // 存档界面返回按钮Y轴坐标

constexpr int FISHING_LAYER_FISHING_BUTTON_OFFSET_Y = 150;                                   // 钓鱼界面钓鱼按钮Y轴偏移量

constexpr int DEFAULT_MUSIC_SIGN = -1;                                                       // 缺省音乐标识
constexpr float DEFAULT_MUSIC_VOLUMN = 0.5f;                                                 // 缺省音量大小

constexpr float NOMAL_PLAYER_SPEED = 100;                                                    // 人物默认移动速度
constexpr int PLAYER_IMAGE_WIDTH = 64;                                                       // 人物移动图集宽度
constexpr int PLAYER_IMAGE_HEIGHT = 128;                                                     // 人物移动图集高度
constexpr int PLAYER_FRAME_RATE = 4;                                                         // 人物移动帧数
constexpr int PLAYER_DIRECTION_NUM = 4;                                                      // 人物可移动方向数
constexpr int PLAYER_FRAME_WIDTH = PLAYER_IMAGE_WIDTH / PLAYER_FRAME_RATE;                   // 每帧宽度（图片宽度/帧数）
constexpr int PLAYER_FRAME_HEIGHT = PLAYER_IMAGE_HEIGHT / PLAYER_DIRECTION_NUM;              // 每帧高度（图片高度/行数）
constexpr float PLAYER_FRAME_DELAY = 0.1f;                                                   // 每帧动画延迟
constexpr int CURRENT_ITEM_OFFSET_X = 8;                                                     // 手中物品与人所在位置X轴偏移量
constexpr int CURRENT_ITEM_OFFSET_Y = 16;                                                    // 手中物品与人所在位置Y轴偏移量

constexpr int DEFAULT_VIEW_HEIGHT = 400;                                                     // 默认视角高度
constexpr int MAX_VIEW_HEIGHT = 500;                                                         // 地图中最大视角高度
constexpr int MIN_VIEW_HEIGHT = 200;                                                         // 地图中最小视角高度

constexpr int MAP_TILE_WIDTH = 16;                                                           // 地图瓦片宽度
constexpr int MAP_TILE_HEIGHT = 16;                                                          // 地图瓦片高度 
constexpr int FARMYARD_MAP_WIDTH = 100;                                                      // FarmYard地图宽度
constexpr int FARMYARD_MAP_HEIGHT = 80;                                                      // FarmYard地图高度
constexpr int FARMHOUSE_MAP_WIDTH = 14;                                                      // FarmHouse地图宽度
constexpr int FARMHOUSE_MAP_HEIGHT = 14;                                                     // FarmHouse地图高度
constexpr int TOWNCENTER_MAP_WIDTH = 60;                                                     // TownCenter地图宽度
constexpr int TOWNCENTER_MAP_HEIGHT = 50;                                                    // TownCenter地图高度

constexpr int TIME_DIPLAY_OFFSET_X = -300;                                                   // 时间显示背景X轴偏移量
constexpr int TIME_DIPLAY_OFFSET_Y = -50;                                                    // 时间显示背景Y轴偏移量

constexpr int DEFAULT_CAPACITY = 30;                                                         // 默认背包容量
constexpr int DEFAULT_BAR = 10;                                                              // 默认物品栏容量

// 物品种类枚举
enum ItemType 
{
	SEED,          // 种子
	TOOL,          // 工具
 	OTHER,         // 其他 
};

// 每种物品的具体描述
const std::string SEED_DESCRIPTION = "Various crop seeds.";
const std::string TOOL_DESCRIPTION = "Farm production tools.";
const std::string OTHER_DESCRIPTION = "Other items.";

// 工具类型枚举
enum ToolType 
{
    HOE,           // 锄头
    WATERING_CAN,  // 浇水壶
    PICKAXE,       // 镐子
    AXE,           // 斧头
    SCYTHE,        // 镰刀
    FISHING_ROD,   // 钓鱼竿
};

// 每种功能的具体描述
const std::string TOOL_HOE_DESCRIPTION = "The hoe is used to till the land.";
const std::string TOOL_WATERING_CAN_DESCRIPTION = "The watering can is used to provide essential water to crops.";
const std::string TOOL_PICKAXE_DESCRIPTION = "The pickaxe is used to break rocks, ores, and other hard objects.";
const std::string TOOL_AXE_DESCRIPTION = "The axe is used to chop trees and obtain wood.";
const std::string TOOL_SCYTHE_DESCRIPTION = "The scythe is used to harvest mature crops or clear weeds.";
const std::string TOOL_FISHING_ROD_DESCRIPTION = "The fishing rod is used for fishing in water.";

// 种子类型枚举
enum SeedType 
{
    RADISH_SEED,
    POTATO_SEED,
    WHEAT_SEED,
};

// 每种种子的具体描述
const std::string SEED_RADISH_DESCRIPTION = "Radishes are fast-growing vegetables.";
const std::string SEED_POTATO_DESCRIPTION = "Potatoes are a high-yield root crop.";
const std::string SEED_WHEAT_DESCRIPTION = "Wheat is mainly used to make bread.";

// 杂物类型枚举
enum OtherType 
{
    FOOD_APPLE,
    FOOD_BREAD,
    FOOD_FRIED_POTATO,
    FOOD_FISH,
    CROP_RADISH,
    CROP_POTATO,
    CROP_WHEAT,
    MATERIAL_WOOD,
    MATERIAL_STONE,
    MATERIAL_GRASS,
    PRESENT_FLOWER,
};

// 每种杂物的具体描述
const std::string OTHER_FOOD_APPLE_DESCRIPTION = "Fresh apples, sweet and delicious.";
const std::string OTHER_FOOD_BREAD_DESCRIPTION = "Bread made from wheat.";
const std::string OTHER_FOOD_FRIED_POTATO_DESCRIPTION = "Potatoes fried in oil.";
const std::string OTHER_FOOD_FISH_DESCRIPTION = "Freshly caught fish.";
const std::string OTHER_CROP_RADISH_DESCRIPTION = "Mature radishes.";
const std::string OTHER_CROP_POTATO_DESCRIPTION = "Mature potatoes.";
const std::string OTHER_CROP_WHEAT_DESCRIPTION = "Mature wheat.";
const std::string OTHER_MATERIAL_WOOD_DESCRIPTION = "Wood obtained by chopping trees, used for building or crafting.";
const std::string OTHER_MATERIAL_STONE_DESCRIPTION = "Stone obtained from mining, used for building or crafting.";
const std::string OTHER_MATERIAL_GRASS_DESCRIPTION = "Grass grown in the fields, used for basic resources.";
const std::string OTHER_PRESENT_FLOWER_DESCRIPTION = "Beautiful flowers, perfect as a gift for friends.";

// 商店操作类型枚举
enum ShopType
{
    SHOP_BUY,      // 购买物品
    SHOP_SELL,     // 卖出物品
    TASK_REWARD,   // 委托奖励
    TASK_PAID,     // 委托所需
    PRESENT,       // 赠送
};

// 每种作物的最大成长阶段
constexpr int OBJECT_RADISH_MAX_STATE = 4;
constexpr int OBJECT_POTATO_MAX_STATE = 5;
constexpr int OBJECT_WHEAT_MAX_STATE = 4;

// 每种成长阶段的资源路径
const std::string OBJECT_RADISH_STATE[OBJECT_RADISH_MAX_STATE] = {
"ImageElements/FarmObjects/RadishState_1.png",
"ImageElements/FarmObjects/RadishState_2.png",
"ImageElements/FarmObjects/RadishState_3.png",
"ImageElements/FarmObjects/RadishState_4.png",
};

const std::string OBJECT_POTATO_STATE[OBJECT_POTATO_MAX_STATE] = {
"ImageElements/FarmObjects/PotatoState_1.png",
"ImageElements/FarmObjects/PotatoState_2.png",
"ImageElements/FarmObjects/PotatoState_3.png",
"ImageElements/FarmObjects/PotatoState_4.png",
"ImageElements/FarmObjects/PotatoState_5.png",
};

const std::string OBJECT_WHEAT_STATE[OBJECT_WHEAT_MAX_STATE] = {
"ImageElements/FarmObjects/WheatState_1.png",
"ImageElements/FarmObjects/WheatState_2.png",
"ImageElements/FarmObjects/WheatState_3.png",
"ImageElements/FarmObjects/WheatState_4.png",
};

// 实例种类
enum ObjectType
{
    TREE,
    WEED,
    STONE,
    RADISH,
    POTATO,
    WHEAT,
};

// 每种对象的碰撞体积
constexpr int OBJECT_TREE_WIDTH = 16;
constexpr int OBJECT_TREE_HEIGHT = 16;
constexpr int OBJECT_WEED_WIDTH = 16;
constexpr int OBJECT_WEED_HEIGHT = 16;
constexpr int OBJECT_STONE_WIDTH = 16;
constexpr int OBJECT_STONE_HEIGHT = 16;
constexpr int OBJECT_CROP_WIDTH = 16;
constexpr int OBJECT_CROP_HEIGHT = 16;

constexpr int DRY_THRESHOLD = 200;

// 土地状态
enum LandState
{
    DRY, 
    WET,
};

// NPC的种类
enum NPCType
{
    ALEX,
    ABIGAIL,
    CAROLINE,
    LEWIS,
};

const std::vector<std::string> NPC_ALEX_DIALOG = {
    " Hey, I'm Alex. \n I'm training to be the best athlete in the valley!",
    " You should try working out at the gym sometime,\n it's a great place to get stronger!",
    " I don't have time for anything that doesn't\n involve my training or football, sorry!",
};

const std::vector<std::string> NPC_ABIGAIL_DIALOG = {
    " Hey, you! You should try the chocolate cake in my room \n sometime. It's the best in town!",
    " I love spending time in the graveyard. \n It’s so peaceful there at night...",
    " Have you ever tried going down into the mines?\n It’s dangerous but also thrilling!",
};

const std::vector<std::string> NPC_CAROLINE_DIALOG = {
    " I've been tending to my garden.\n Nothing makes me happier than seeing my flowers bloom.",
    " My daughter Abigail can be a bit difficult at times,\n but she’s still my precious girl.",
    " The valley is so peaceful in the spring.\n I love it when the flowers start blooming.",
};

const std::vector<std::string> NPC_LEWIS_DIALOG = {
    " Welcome to Pelican Town!\n I'm Lewis, the mayor.\n Let me know if you need anything.",
    " It's important to help out the community,\n whether it's by donating to the local fund\n or assisting with town events.",
    " The people of this town are what make it special.\n We need to take care of each other.",
};

#endif // _CONSTANT_H_
