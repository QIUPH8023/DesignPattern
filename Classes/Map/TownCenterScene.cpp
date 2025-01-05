#include "TownCenterScene.h"
#include "FarmYardScene.h"
#include "../Player/Player.h"
#include "../GameTime/GameTimeLayer.h"
#include "proj.win32/Constant.h"
#include "../Music/AudioPlayer.h"

USING_NS_CC;

Scene* TownCenterScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TownCenterScene::create();
	scene->addChild(layer);
	auto gametimeLayer = GameTimeLayer::create();
	scene->addChild(gametimeLayer, 10);
	auto inventorylayer = InventoryLayer::create();
	scene->addChild(inventorylayer, 10);
	return scene;
}

bool TownCenterScene::init()
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
	auto TownCentre = TMXTiledMap::create("Maps/Town.tmx");
	if (!TownCentre) {
		CCLOG("Failed to load tile map");
		return false;
	}
	TownCentre->getLayer("Meta")->setVisible(false);
	TownCentre->setPosition(0, 0);
	TownCentre->setCameraMask(unsigned short(CameraFlag::USER1));
	this->addChild(TownCentre, 0, "TownCentre");

	// 获取地图的基础属性
	auto objectGroup = TownCentre->getObjectGroup("Event");
	if (!objectGroup) {
		CCLOG("Failed to load object layer: Event");
		return false;
	}

	auto spawnPoint = objectGroup->getObject("SpawnPoint");
	auto townToYard = objectGroup->getObject("TownToYard");
	// 获取NPC位置
	auto abigail= objectGroup->getObject("Abigail");
	auto alex = objectGroup->getObject("Alex");
	auto caroline = objectGroup->getObject("Caroline");
	auto lewis = objectGroup->getObject("Lewis");
	if (spawnPoint.empty() || townToYard.empty() ||
		abigail.empty() || alex.empty() || caroline.empty() || lewis.empty()) {
		CCLOG("Event not found in Event layer.");
		return false;
	}

	// 创建一个矩形表示 townToYard 区域
	townToYardRect.setRect(townToYard["x"].asFloat(), townToYard["y"].asFloat(), townToYard["width"].asFloat(), townToYard["height"].asFloat());

	auto player = Player::getInstance();
	player->init();
	player->setPosition(spawnPoint["x"].asFloat(), spawnPoint["y"].asFloat());
	player->setCameraMask(unsigned short(CameraFlag::USER1));
	this->addChild(player, 2, "player");

	// 创建NPC
	Abigail = NPC::create("NPC/Abigail.png",ABIGAIL);
	Abigail->setAnchorPoint(Vec2(0.5, 0));
	Abigail->setPosition(abigail["x"].asFloat(), abigail["y"].asFloat());
	Abigail->setCameraMask(unsigned short(CameraFlag::USER1));
	Alex = NPC::create("NPC/Alex.png",ALEX);
	Alex->setAnchorPoint(Vec2(0.5, 0));
	Alex->setPosition(alex["x"].asFloat(), alex["y"].asFloat());
	Alex->setCameraMask(unsigned short(CameraFlag::USER1));
	Caroline = NPC::create("NPC/Caroline.png",CAROLINE);
	Caroline->setAnchorPoint(Vec2(0.5, 0));
	Caroline->setPosition(caroline["x"].asFloat(), caroline["y"].asFloat());
	Caroline->setCameraMask(unsigned short(CameraFlag::USER1));
	Lewis = NPC::create("NPC/Lewis.png",LEWIS);
	Lewis->setAnchorPoint(Vec2(0.5, 0));
	Lewis->setPosition(lewis["x"].asFloat(), lewis["y"].asFloat());
	Lewis->setCameraMask(unsigned short(CameraFlag::USER1));

	this->addChild(Abigail, 1, "Abigail");
	this->addChild(Alex, 1, "Alex");
	this->addChild(Caroline, 1, "Caroline");
	this->addChild(Lewis, 1, "Lewis");

	// 创建并注册鼠标滚轮和鼠标点击事件监听器
	registerMouseScrollListener();
	registerMouseClickListener();

	// 启动每帧更新函数
	this->scheduleUpdate();

	return true;
}

void TownCenterScene::update(float delta)
{
	Player* player = Player::getInstance();

	// 获取 TownCentre 地图对象
	auto TownCentre = (TMXTiledMap*)this->getChildByName("TownCentre");

	// 计算摄像机的位置
	Vec3 currentCameraPos = camera->getPosition3D();

	// 获得玩家的当前位置
	Vec2 currentPosition = player->getPosition();

	// 计算更新后的位置
	Vec2 newPosition = currentPosition + player->getDirection() * player->getSpeed() * delta;

	// 获取玩家目标位置的瓦片GID
	int tileGID = TownCentre->getLayer("Meta")->getTileGIDAt(convertToTileCoords(newPosition));
	if (tileGID) {
		// 获取瓦片属性
		auto properties = TownCentre->getPropertiesForGID(tileGID).asValueMap();
		if (!properties.empty() && properties["Collidable"].asBool()) {
			// 判断瓦片是否具有 "Collidable" 属性且为 true
			// 如果该瓦片不可通行，则直接返回，不更新玩家位置
			return;
		}
	}

	// 更新玩家位置
	player->setPosition(newPosition);

	if (townToYardRect.containsPoint(newPosition)) {
		// 在切换场景之前，先禁用更新
		this->unscheduleUpdate();

		this->removeChild(player);
		player->resetInit();
		Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, FarmYardScene::createScene(), cocos2d::Color3B::WHITE));
	}

	Vec2 newtile = convertToTileCoords(newPosition);
	Vec2 faceto = player->getFaceto();
	targetRect.setRect((newtile.x + faceto.x) * MAP_TILE_WIDTH, (TOWNCENTER_MAP_HEIGHT - newtile.y + faceto.y) * MAP_TILE_HEIGHT, MAP_TILE_WIDTH, MAP_TILE_HEIGHT);

	// 计算摄像头目标位置
	Vec3 targetCameraPos(newPosition.x, newPosition.y, currentCameraPos.z);
	// 平滑移动摄像机
	camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 0.1f));// 平滑系数

}

// 鼠标滚动监听器
void TownCenterScene::registerMouseScrollListener()
{
	// 创建鼠标事件监听器
	auto listener = EventListenerMouse::create();
	listener->onMouseScroll = CC_CALLBACK_1(TownCenterScene::onMouseScroll, this);

	// 获取事件分发器并添加监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void TownCenterScene::onMouseScroll(cocos2d::EventMouse* event)
{
	// 获取滚动增量
	auto scrollDelta = event->getScrollY();  

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

// 鼠标点击监听器
void TownCenterScene::registerMouseClickListener()
{
	// 播放按键声音
	audioPlayer(CLICK_SOUND_EFFECT_PATH);

	// 创建鼠标点击事件监听器
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(TownCenterScene::onMouseClick, this);

	// 获取事件分发器并添加监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void TownCenterScene::onMouseClick(cocos2d::EventMouse* event)
{
	Player* player = Player::getInstance();

	// 获取 FarmYard 地图对象
	auto TownCentre = (TMXTiledMap*)this->getChildByName("TownCentre");

	// 判断鼠标点击的按钮
	auto mouseButton = event->getMouseButton();
	if (mouseButton == EventMouse::MouseButton::BUTTON_RIGHT) {
		CCLOG("Right mouse button clicked");
		// 执行右键点击相关操作
		if (targetRect.containsPoint(Abigail->getPosition())) {
			CCLOG("Abigail");
			auto chatlayer = ChatLayer::create(Abigail);
			chatlayer->setAnchorPoint(Vec2(0, 0));
			chatlayer->setPosition(Vec2(0, 0));
			this->addChild(chatlayer, 1, "chatlayer");

		}
		else if(targetRect.containsPoint(Alex->getPosition())) {
			CCLOG("Alex");
			auto chatlayer = ChatLayer::create(Alex);
			chatlayer->setAnchorPoint(Vec2(0, 0));
			chatlayer->setPosition(Vec2(0, 0));
			this->addChild(chatlayer, 1, "chatlayer");


		}
		else if (targetRect.containsPoint(Caroline->getPosition())) {
			CCLOG("Caroline");
			auto chatlayer = ChatLayer::create(Caroline);
			chatlayer->setAnchorPoint(Vec2(0, 0));
			chatlayer->setPosition(Vec2(0, 0));
			this->addChild(chatlayer, 1, "chatlayer");


		}
		else if (targetRect.containsPoint(Lewis->getPosition())) {
			CCLOG("Lewis");
			auto chatlayer = ChatLayer::create(Lewis);
			chatlayer->setAnchorPoint(Vec2(0, 0));
			chatlayer->setPosition(Vec2(0, 0));
			this->addChild(chatlayer, 1, "chatlayer");


		}
	}
	// 防止事件传播
	event->stopPropagation();
}

Vec2 TownCenterScene::convertToTileCoords(const Vec2& pos)
{
	// 将玩家的新位置转换为瓦片坐标
	Vec2 tile = Vec2(int(pos.x / MAP_TILE_WIDTH), int((TOWNCENTER_MAP_HEIGHT * MAP_TILE_HEIGHT - pos.y) / MAP_TILE_HEIGHT));

	return tile;
}
