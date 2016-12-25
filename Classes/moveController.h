#ifndef __MOVE_CONTROLLER_H__
#define __MOVE_CONTROLLER_H__

#include "cocos2d.h"
#include "controllerListener.h"
#include "controller.h"

class MoveController : public Controller
{
public:
	MoveController() {};
	~MoveController() {};
	CREATE_FUNC(MoveController);
	virtual bool init();
	virtual void update(float dt);
		
	void setiSpeedX(float iSpeedX);
	void setiSpeedY(float iSpeedY);
	cocos2d::Vec2 getiSpeed();
	void setAccelerateY(float AccelerateY);
private:
	cocos2d::Vec2 m_iSpeed;
	cocos2d::Vec2 m_accelerate;
};

#endif