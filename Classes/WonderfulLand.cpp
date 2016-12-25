#include "WonderfulLand.h"
#include "player.h"
#include "npc.h"
#include "UI.h"

#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;

Scene * WonderfulLand::createScene()
{
	return WonderfulLand::create();
}

bool WonderfulLand::init()
{
	if (!Scene::init())
		return false;

	srand((unsigned)time(nullptr));

	createCamera();
	createSky();
	createMap();
	createMoveController();
	createNPC();//need map
	createPlayer();// need map, controller, camera
	createUI();//need controller, player

	return true;
}

void WonderfulLand::createPlayer()
{
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Animation/NewProject.ExportJson");
	Armature *armature = Armature::create("NewProject");
	/* armature
	0 for walk
	1 for blink
	2 for breathe
	3 for stand
	4 for do something
	*/
	armature->getAnimation()->playWithIndex(3);
	armature->getAnimation()->setSpeedScale(0.5f);
	armature->setCameraMask(2);

	player = Player::create();
	player->bindSprite(armature);
	this->addChild(player,5);

	TMXObjectGroup* objGroup = map->getObjectGroup("player");
	ValueMap playerPoint = objGroup->getObject("player");
	float playerX = playerPoint["x"].asFloat() + playerPoint["width"].asFloat() * 0.5f;
	float playerY = playerPoint["y"].asFloat() + playerPoint["height"].asFloat() * 0.5f;

	player->setPosition(playerX, playerY);

	player->setController(moveController);

	player->setTiledMap(map);

	player->setCamera(_camera);
}

void WonderfulLand::createSky()
{
	Size size = Director::getInstance()->getWinSize();
	auto sprite = Sprite::create("sky01.png");
	sprite->setCameraMask(2);
	sprite->setScaleX(size.width/sprite->getContentSize().width);
	sprite->setScaleY(size.height/sprite->getContentSize().height);
	sprite->setPosition(size.width / 2, size.height / 2);
	_camera->addChild(sprite);
}

void WonderfulLand::createCamera()
{
	Size size = Director::getInstance()->getWinSize();
	_camera = Camera::createOrthographic(size.width, size.height, -2048, 2048);
	_camera->setCameraFlag(CameraFlag::USER1);
	_camera->setPosition3D(Vec3::ZERO);
	this->addChild(_camera);
}

void WonderfulLand::createMap()
{
	map = TMXTiledMap::create("map_school.tmx");
	map->setCameraMask(2);
	this->addChild(map);
}

void WonderfulLand::createMoveController()
{
	moveController = MoveController::create();
	this->addChild(moveController);
}

void WonderfulLand::createUI()
{
	Size size = Director::getInstance()->getWinSize();
	//walk button
	auto walk_box_sprite = Sprite::create("glass_button.png");

	auto walkControlBox = WalkControlButton::create();
	walkControlBox->bindSprite(walk_box_sprite);
	walkControlBox->bindPlayer(player);
	walkControlBox->setPosition(size.width * 0.12, size.height * 0.2);
	walkControlBox->setScaleX(1.5f);
	this->addChild(walkControlBox);

	//jump button
	auto jump_box_sprite = Sprite::create("glass_button.png");

	auto jumpControlBox = JumpControlButton::create();
	jumpControlBox->bindSprite(jump_box_sprite);
	jumpControlBox->bindPlayer(player);
	jumpControlBox->setPosition(size.width * 0.88, size.height * 0.2);
	jumpControlBox->setScaleX(1.f);
	this->addChild(jumpControlBox);
}

void WonderfulLand::createNPC()
{
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Animation/NewProject.ExportJson");
	Armature *armature = Armature::create("NewProject");
	armature->getAnimation()->playWithIndex(3);
	armature->getAnimation()->setSpeedScale(0.5f);
	armature->setCameraMask(2);

	auto npc = Npc::create();
	npc->bindSprite(armature);
	this->addChild(npc, 5);

	TMXObjectGroup* objGroup = map->getObjectGroup("player");
	ValueMap playerPoint = objGroup->getObject("npc1");
	float npcX = playerPoint["x"].asFloat() + playerPoint["width"].asFloat() * 0.5f;
	float npcY = playerPoint["y"].asFloat() + playerPoint["height"].asFloat() * 0.5f;
	npc->setPosition(npcX, npcY);

	npc->setTiledMap(map);

	auto moveController1 = MoveController::create();
	this->addChild(moveController1);
	npc->setController(moveController1);

	npc->setState(WANDER);
}
