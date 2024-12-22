/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmYardScene.cpp
 * File Function: FarmYardScene类的实现
 * Author:        张翔
 * Update Date:   2024/12/5
 ****************************************************************/

#include "FarmYardScene.h"
#include "FarmHouseScene.h"
#include "TownCenterScene.h"
#include "../Item/Item.h"
#include "../Player/Player.h"
#include "../GameTime/GameTimeLayer.h"
#include "../Manager/Manager.h"
#include "../Inventory/InventoryLayer.h"
#include "../FishingGame/FishingGame.h"
#include "../Music/AudioPlayer.h"
USING_NS_CC;

// 创建场景
Scene* FarmYardScene::createScene()
{
	auto scene = Scene::create();
	auto farmlayer = FarmYardScene::create();
	scene->addChild(farmlayer, 0);
	auto gametimeLayer = GameTimeLayer::create();
	scene->addChild(gametimeLayer, 10);
	auto inventorylayer = InventoryLayer::create();
	scene->addChild(inventorylayer, 10);
	return scene;
}

// 初始化场景
bool FarmYardScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	// 创建摄像机
	camera = Camera::create();
	camera->setCameraFlag(CameraFlag::USER1);
	camera->setDepth(-1);
	cocos2d::Vec3 currentPos = camera->getPosition3D();
	currentPos.z = DEFAULT_VIEW_HEIGHT;
	camera->setPosition3D(currentPos);
	this->addChild(camera);

	// 加载瓦片地图
	auto FarmYard = TMXTiledMap::create("Maps/FarmYardScene.tmx");
	if (!FarmYard) {
		CCLOG("Failed to load tile map");
		return false;
	}
	FarmYard->getLayer("Meta")->setVisible(false);
	FarmYard->setCameraMask(unsigned short(CameraFlag::USER1));
	this->addChild(FarmYard, 0, "FarmYard");

	// 获取地图的基础属性
	auto objectGroup = FarmYard->getObjectGroup("Event");
	auto spawnPoint = objectGroup->getObject("SpawnPoint");
	auto yardToHouse = objectGroup->getObject("YardToHouse");
	auto yardToTown = objectGroup->getObject("YardToTown");
	if (!objectGroup||spawnPoint.empty()|| yardToHouse.empty() || yardToTown.empty()) {
		CCLOG("Event not found in Event layer.");
		return false;
	}

	// 初始化传送点
	yardToHouseRect.setRect(yardToHouse["x"].asFloat(), yardToHouse["y"].asFloat(), yardToHouse["width"].asFloat(), yardToHouse["height"].asFloat());
	yardToTownRect.setRect(yardToTown["x"].asFloat(), yardToTown["y"].asFloat(), yardToTown["width"].asFloat(), yardToTown["height"].asFloat());

	auto player = Player::getInstance();
	player->init();
	player->setPosition(spawnPoint["x"].asFloat(), spawnPoint["y"].asFloat());
	player->setCameraMask(unsigned short(CameraFlag::USER1));
	this->addChild(player, 1, "player");

	targettile = Sprite::create("ImageElements/TargetTile.png");
	targettile->setAnchorPoint(Vec2(0, 0));
	targettile->setCameraMask(unsigned short(CameraFlag::USER1));
	this->addChild(targettile, 1, "targettile");

	// 创建并注册鼠标滚轮和鼠标点击事件监听器
	registerMouseScrollListener();
	registerMouseClickListener();

	// 加载从农场中的事物
	Manager::getInstance();

	// 启动每帧更新函数
	this->scheduleUpdate();

	return true;
}

// 更新函数
void FarmYardScene::update(float delta)
{
	if (this->getChildByName("fishgame") != nullptr) {
		// 如果有钓鱼游戏界面，就不更新地图
		return;
	}

	Player* player = Player::getInstance();

	// 获取 FarmYard 地图对象
	auto FarmYard = (TMXTiledMap*)this->getChildByName("FarmYard");

	// 计算摄像机的位置
	Vec3 currentCameraPos = camera->getPosition3D();

	// 获得玩家的当前位置
	Vec2 currentPosition = player->getPosition();

	// 获取瓦片图层
	auto tileLayer = FarmYard->getLayer("Meta");
	if (!tileLayer) {
		CCLOG("Layer not found");
		return;
	}

	// 计算更新后的位置
	Vec2 newPosition = currentPosition + player->getDirection() * player->getSpeed() * delta;

	// 获取玩家目标位置的瓦片GID
	int tileGID = tileLayer->getTileGIDAt(convertToTileCoords(newPosition));
	if (tileGID) {
		// 获取瓦片属性
		auto properties = FarmYard->getPropertiesForGID(tileGID).asValueMap();
		if (!properties.empty()&& properties["Collidable"].asBool()) {
			// 如果该瓦片不可通行，则直接返回，不更新玩家位置
			return;
		}
	}

	// 更新玩家位置
	player->setPosition(newPosition);

	if (yardToHouseRect.containsPoint(newPosition)) {
		// 在切换场景之前，先禁用更新
		this->unscheduleUpdate();
		Manager::getInstance()->saveGameState("Archive/ManagerDefaultArchive.json");
		Manager::getInstance()->removeFromScene();
		this->removeChild(player);
		player->resetInit();
		Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, FarmHouseScene::createScene(), cocos2d::Color3B::WHITE));
	}
	else if (yardToTownRect.containsPoint(newPosition)) {
		// 在切换场景之前，先禁用更新
		this->unscheduleUpdate();
		Manager::getInstance()->saveGameState("Archive/ManagerDefaultArchive.json");
		Manager::getInstance()->removeFromScene();
		this->removeChild(player);
		player->resetInit();
		Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, TownCenterScene::createScene(), cocos2d::Color3B::WHITE));
	}

	Vec2 newtile = convertToTileCoords(newPosition);
	Vec2 faceto = player->getFaceto();
	targettile->setPosition(Vec2((newtile.x + faceto.x) * MAP_TILE_WIDTH, (FARMYARD_MAP_HEIGHT - newtile.y+ faceto.y) * MAP_TILE_HEIGHT));

	// 计算摄像头目标位置
	Vec3 targetCameraPos(newPosition.x, newPosition.y, currentCameraPos.z);
	// 平滑移动摄像机
	camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 0.1f));
}

// 注册鼠标滚轮监听器
void FarmYardScene::registerMouseScrollListener()
{
	// 创建鼠标事件监听器
	mouseScrollListener = EventListenerMouse::create();
	mouseScrollListener->onMouseScroll = CC_CALLBACK_1(FarmYardScene::onMouseScroll, this);

	// 获取事件分发器并添加监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseScrollListener, this);
}

// 鼠标滚轮事件回调
void FarmYardScene::onMouseScroll(cocos2d::EventMouse* event)
{
	auto scrollDelta = event->getScrollY();  // 获取滚动增量
	CCLOG("Mouse Scroll Delta: %f", scrollDelta);
	// 计算摄像机的位置
	Vec3 currentCameraPos = camera->getPosition3D();

	if ((currentCameraPos.z <= MIN_VIEW_HEIGHT && scrollDelta < 0) ||
		(currentCameraPos.z >= MAX_VIEW_HEIGHT && scrollDelta > 0))
		return;

	// 计算摄像头目标位置
	Vec3 targetCameraPos(currentCameraPos.x, currentCameraPos.y, currentCameraPos.z + 100 * scrollDelta);
	// 平滑移动摄像机
	camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 0.1f));
}

// 注册鼠标点击监听器
void FarmYardScene::registerMouseClickListener()
{
	// 创建鼠标点击事件监听器
	mouseClickListener = EventListenerMouse::create();
	mouseClickListener->onMouseDown = CC_CALLBACK_1(FarmYardScene::onMouseClick, this);

	// 获取事件分发器并添加监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseClickListener, this);
}

// 鼠标点击事件回调
void FarmYardScene::onMouseClick(cocos2d::EventMouse* event)
{
	// 获取 FarmYard 地图对象
	auto FarmYard = (TMXTiledMap*)this->getChildByName("FarmYard");

	auto Manager = Manager::getInstance();

	auto targetpos = targettile->getPosition();

	int currentHeldItem = Inventory::getInstance()->getCurrHeldItem();
	auto heldItem = Inventory::getInstance()->getSlot(currentHeldItem).getItem();
	std::shared_ptr<Tool> heldTool = std::dynamic_pointer_cast<Tool>(heldItem);
	std::shared_ptr<Seed> heldSeed = std::dynamic_pointer_cast<Seed>(heldItem);

	// 如果手中没有拿任何东西
	if (heldItem == nullptr)
		return;

	// 获取瓦片图层
	auto tileLayer = FarmYard->getLayer("Meta");
	if (!tileLayer) {
		CCLOG("Layer not found");
		return;
	}

	// 判断鼠标点击的按钮
	auto mouseButton = event->getMouseButton();
	if (mouseButton == EventMouse::MouseButton::BUTTON_LEFT) {
		CCLOG("Left mouse button clicked");

		// 创建动画对象
		auto currItem = Sprite::create(Inventory::getInstance()->getSlot(currentHeldItem).getItem()->getImagePath());
		currItem->setAnchorPoint(Vec2(0, 0));
		currItem->setPosition(targetpos);
		currItem->setCameraMask(unsigned short(CameraFlag::USER1));
		// 获取玩家目标位置的瓦片GID
		int tileGID = tileLayer->getTileGIDAt(convertToTileCoords(Player::getInstance()->getPosition()));
		if (heldTool) {
			switch (heldTool->getSubType()) {
			case HOE:
				if (tileGID) {
					auto properties = FarmYard->getPropertiesForGID(tileGID).asValueMap();
					if (properties["Plowable"].asBool()) {
						CCLOG("使用锄头进行耕地");
						this->addChild(currItem, 3);
						currItem->runAction(Sequence::create(   // 执行动画
							RotateBy::create(0.2f, 45),         // 旋转动画
							RotateBy::create(0.2f, -45),        // 还原旋转
							DelayTime::create(0.5f),            // 延迟 0.5 秒
							CallFunc::create([=]() {
								this->removeChild(currItem);             // 动画完成后移除精灵
								}),
							nullptr));
						// 执行操作
						Manager::getInstance()->addFarmland(targetpos.x, targetpos.y, this);
					}
				}
				break;
			case FISHING_ROD:
				if (tileGID) {
					auto properties = FarmYard->getPropertiesForGID(tileGID).asValueMap();
					if (properties["FishAllowed"].asBool()) {
						CCLOG("使用鱼竿进行钓鱼");
						this->addChild(currItem, 3);
						currItem->runAction(Sequence::create(
							MoveBy::create(0.5f, Vec2(0, 30)),
							MoveBy::create(0.5f, Vec2(0, -30)),
							DelayTime::create(0.5f),
							CallFunc::create([=]() {
								this->removeChild(currItem);
								}),
							nullptr));
						// 执行操作
						if (this->getChildByName("fishgame") == nullptr) {
							FishingGame* fishingGame = FishingGame::create();
							this->addChild(fishingGame, 10, "fishgame");
							fishingGame->FishingGameStart();
						}
					}
				}
				break;
			case WATERING_CAN:
				if (Manager->findFarmlandByPosition(targetpos.x, targetpos.y) != nullptr) {
					CCLOG("使用水壶进行浇水");
					this->addChild(currItem, 3);
					currItem->runAction(Sequence::create(
						MoveBy::create(0.5f, Vec2(0, 20)),
						MoveBy::create(0.5f, Vec2(0, -20)),
						DelayTime::create(0.5f),
						CallFunc::create([=]() {
							this->removeChild(currItem);
							}),
						nullptr));
					// 执行操作
					Manager->findFarmlandByPosition(targetpos.x, targetpos.y)->watering();
				}
				break;
			case PICKAXE:
				if (Manager->findObjectByPosition(targetpos.x, targetpos.y)->getObjectType() == STONE) {
					CCLOG("使用镐子进行挖矿");
					this->addChild(currItem, 3);
					currItem->runAction(Sequence::create(
						ScaleBy::create(0.2f, 1.2f),
						ScaleBy::create(0.2f, 0.833f),
						DelayTime::create(0.5f),
						CallFunc::create([=]() {
							this->removeChild(currItem);
							}),
						nullptr));
					// 执行操作

				}
				break;
			case AXE:
				if (Manager->findObjectByPosition(targetpos.x, targetpos.y)->getObjectType() == TREE) {
					CCLOG("使用斧子进行砍树");
					this->addChild(currItem, 3);
					currItem->runAction(Sequence::create(
						RotateBy::create(0.2f, 45),
						RotateBy::create(0.2f, -45),
						DelayTime::create(0.5f),
						CallFunc::create([=]() {
							this->removeChild(currItem);
							}),
						nullptr));
					// 执行操作

				}
				break;
			case SCYTHE:
				if (Manager->findObjectByPosition(targetpos.x, targetpos.y)->getObjectType() == WEED) {
					CCLOG("使用镰刀进行除草");
					this->addChild(currItem, 3);
					currItem->runAction(cocos2d::Sequence::create(
						cocos2d::MoveBy::create(0.3f, cocos2d::Vec2(20, 0)),
						cocos2d::MoveBy::create(0.3f, cocos2d::Vec2(-20, 0)),
						cocos2d::DelayTime::create(0.5f),
						cocos2d::CallFunc::create([=]() {
							this->removeChild(currItem);
							}),
						nullptr));
					// 执行操作

				}
				break;
			default:
				break;
			}
		}
		else if (heldSeed) {
			switch (heldSeed->getSubType()) {
			case RADISH_SEED:
				if (Manager->findFarmlandByPosition(targetpos.x, targetpos.y) != nullptr &&
					Manager->findObjectByPosition(targetpos.x, targetpos.y) == nullptr) {
					this->addChild(currItem, 3);
					currItem->runAction(cocos2d::Sequence::create(
						MoveTo::create(0.5f, targetpos), // 种子飞行动画
						DelayTime::create(0.5f),         // 延迟 0.5 秒
						CallFunc::create([=]() {
							// 播种完成后移除精灵
							this->removeChild(currItem);
							Manager::getInstance()->addObject(RADISH, targetpos.x, targetpos.y, this);
							}),
						nullptr));
				}
				break;
			case POTATO_SEED:
				if (Manager->findFarmlandByPosition(targetpos.x, targetpos.y) != nullptr &&
					Manager->findObjectByPosition(targetpos.x, targetpos.y) == nullptr) {
					this->addChild(currItem, 3);
					currItem->runAction(cocos2d::Sequence::create(
						MoveTo::create(0.5f, targetpos), // 种子飞行动画
						DelayTime::create(0.5f),         // 延迟 0.5 秒
						CallFunc::create([=]() {
							// 播种完成后移除精灵
							this->removeChild(currItem);
							Manager::getInstance()->addObject(POTATO, targetpos.x, targetpos.y, this);
							}),
						nullptr));
				}
				break;
			case WHEAT_SEED:
				if (Manager->findFarmlandByPosition(targetpos.x, targetpos.y) != nullptr &&
					Manager->findObjectByPosition(targetpos.x, targetpos.y) == nullptr) {
					this->addChild(currItem, 3);
					currItem->runAction(cocos2d::Sequence::create(
						MoveTo::create(0.5f, targetpos), // 种子飞行动画
						DelayTime::create(0.5f), // 延迟 0.5 秒
						CallFunc::create([=]() {
							// 播种完成后移除精灵
							this->removeChild(currItem);
							Manager::getInstance()->addObject(WHEAT, targetpos.x, targetpos.y, this);
							}),
						nullptr));
				}
				break;
			default:
				break;
			}
		}
	}

	// 防止事件传播
	event->stopPropagation();
	audioPlayer(ClickSoundEffect_Path);
}

// 控制事件监听器的禁用
void FarmYardScene::disableEventListeners()
{
	// 移除事件监听器来禁用事件
	if (mouseScrollListener) {
		_eventDispatcher->removeEventListener(mouseScrollListener);
	}
	if (mouseClickListener) {
		_eventDispatcher->removeEventListener(mouseClickListener);
	}
}

// 控制事件监听器的启用
void FarmYardScene::enableEventListeners()
{
	// 恢复事件监听器
	if (mouseScrollListener) {
		_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseScrollListener, this);
	}
	if (mouseClickListener) {
		_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseClickListener, this);
	}
}

// 世界坐标和瓦片坐标的转换
Vec2 FarmYardScene::convertToTileCoords(const Vec2& pos)
{
	// 将玩家的新位置转换为瓦片坐标
	Vec2 tile = Vec2(int(pos.x / MAP_TILE_WIDTH), int((FARMYARD_MAP_HEIGHT * MAP_TILE_HEIGHT - pos.y) / MAP_TILE_HEIGHT));

	return tile;
}
