#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "controllerListener.h"
#include "controller.h"
#include "moveController.h"

class Entity : public cocos2d::Node, public ControllerListener
{
public:
	void setController(MoveController* controller);

	virtual void setTagPosition(float x, float y);
	virtual cocos2d::Vec2 getTagPosition();
protected:
	MoveController* m_controller;
};

#endif