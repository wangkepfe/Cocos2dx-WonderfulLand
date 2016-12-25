#ifndef __CONTROLLER_LISTENER_H__
#define __CONTROLLER_LISTENER_H__

#include "cocos2d.h"

class ControllerListener
{
public:
	ControllerListener() {};
	~ControllerListener() {};
	virtual void setTagPosition(float x,float y) = 0;
	virtual cocos2d::Vec2 getTagPosition() = 0;
};

#endif