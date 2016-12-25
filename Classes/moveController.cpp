#include "moveController.h"

USING_NS_CC;

bool MoveController::init()
{
	m_iSpeed = Vec2::ZERO;
	m_accelerate = Vec2::ZERO;
	this->scheduleUpdate();

	return true;
}

void MoveController::update(float dt)
{
	if (m_controllerListener == NULL)
	{
		return;
	}
	Vec2 pos = m_controllerListener->getTagPosition();
	m_iSpeed = m_iSpeed + m_accelerate;
	pos = pos + m_iSpeed;
	m_controllerListener->setTagPosition(pos.x, pos.y);
}

void MoveController::setiSpeedX(float iSpeedX)
{
	m_iSpeed.x = iSpeedX;
}

void MoveController::setiSpeedY(float iSpeedY)
{
	m_iSpeed.y = iSpeedY;
}

cocos2d::Vec2 MoveController::getiSpeed()
{
	return m_iSpeed;
}

void MoveController::setAccelerateY(float AccelerateY)
{
	m_accelerate.y = AccelerateY;
}
