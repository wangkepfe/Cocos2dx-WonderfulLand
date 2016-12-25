#include"entity.h"

void Entity::setController(MoveController * controller)
{
	m_controller = controller;
	m_controller->setControllerListener(this);
}

void Entity::setTagPosition(float x, float y)
{
	setPosition(x, y);
}

cocos2d::Vec2 Entity::getTagPosition()
{
	return getPosition();
}
