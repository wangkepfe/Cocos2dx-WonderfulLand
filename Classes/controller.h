#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "cocos2d.h"
#include "controllerListener.h"

class Controller : public cocos2d::Node
{
public:
	Controller() {};
	~Controller() {};
	void setControllerListener(ControllerListener* controllerListener);
protected:
	ControllerListener* m_controllerListener;
};


#endif