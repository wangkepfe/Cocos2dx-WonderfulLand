#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "human.h"
#include "ThinkMenu.h"

enum CameraPosition {
	BOTTOM_CENTER,
	BOTTOM_RIGHT,
	BOTTOM_LEFT,
	CENTER,
	STILL
};

struct MyEvent {
	std::string objectGroupName;
	std::string objectName;
	ThinkMenuFunc menuFunc;
};

class Player : public Human
{
public:
	CREATE_FUNC(Player);
	virtual bool init();
	virtual void update(float dt);
	void setCamera(cocos2d::Camera* camera);

	void moveCameraPosition();
	void setCameraPosition();

	void eventUpdate(float dt);
	void loadEvents();
	void eventTriger(float dt);
	void sceneTransform();

	CameraPosition cameraPosition;
private:
	int last_layer;
	float timeCountEvent;
	int inEvent;
	cocos2d::Camera* m_camera;
	ThinkMenu* m_menu;
	MyEvent myEvent[10];
	int myEventNum;
};

#endif