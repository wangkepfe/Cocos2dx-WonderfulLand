#ifndef __WONDERFUL_LAND_H__
#define __WONDERFUL_LAND_H__

#include "cocos2d.h"
#include "moveController.h"
#include "player.h"

class WonderfulLand : public cocos2d::Scene
{
public:
	CREATE_FUNC(WonderfulLand);

	static cocos2d::Scene* createScene();

	WonderfulLand() {};
	virtual ~WonderfulLand() {};

	virtual bool init() override;
	void createPlayer();
	void createSky();
	void createCamera();
	void createUI();
	void createNPC();
	void createMap();
	void createMoveController();
private:
	cocos2d::Camera *_camera;
	MoveController* moveController;
	cocos2d::TMXTiledMap* map;
	Player* player;
};

#endif
