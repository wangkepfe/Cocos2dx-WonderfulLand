#include "UI.h"

USING_NS_CC;

bool WalkControlButton::init()
{
	onPress = false;

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(WalkControlButton::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(WalkControlButton::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(WalkControlButton::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void WalkControlButton::onTouchesBegan(const std::vector<Touch*>& touches, Event * event)
{
	if (m_sprite && m_player)
	{
		Size size = Director::getInstance()->getWinSize();

		auto touch = touches[0];
		auto location = touch->getLocationInView();


		location.y = size.height - location.y;
		if (getPositionX() + m_sprite->getContentSize().width / 2 > location.x &&
			getPositionX() - m_sprite->getContentSize().width / 2 < location.x &&
			getPositionY() + m_sprite->getContentSize().height / 2 > location.y &&
			getPositionY() - m_sprite->getContentSize().height / 2 < location.y)
		{
			onPress = 1;
			if (location.x > getPositionX())
			{
				m_player->moveMode = WALK_RIGHT;
			}
			else
			{
				m_player->moveMode = WALK_LEFT;
			}
		}
	}
}

void WalkControlButton::onTouchesMoved(const std::vector<Touch*>& touches, Event * event)
{
	if (m_sprite && m_player)
	{
		Size size = Director::getInstance()->getWinSize();

		auto touch = touches[0];
		auto location = touch->getLocationInView();

		if (onPress)
		{
			if (location.x > getPositionX())
			{
				m_player->moveMode = WALK_RIGHT;
			}
			else
			{
				m_player->moveMode = WALK_LEFT;
			}
		}
	}
}

void WalkControlButton::onTouchesEnded(const std::vector<Touch*>& touches, Event * event)
{
	m_player->moveMode = STAND;
	onPress = 0;
}

bool JumpControlButton::init()
{
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(JumpControlButton::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(JumpControlButton::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(JumpControlButton::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void JumpControlButton::onTouchesBegan(const std::vector<Touch*>& touches, Event * event)
{
	if (m_sprite && m_player)
	{
		Size size = Director::getInstance()->getWinSize();

		auto touch = touches[0];
		auto location = touch->getLocationInView();
		location.y = size.height - location.y;
		if (getPositionX() + m_sprite->getContentSize().width / 2 > location.x &&
			getPositionX() - m_sprite->getContentSize().width / 2 < location.x &&
			getPositionY() + m_sprite->getContentSize().height / 2 > location.y &&
			getPositionY() - m_sprite->getContentSize().height / 2 < location.y)
		{
			m_player->jumpMode = JUMP;
		}
	}
}

void JumpControlButton::onTouchesMoved(const std::vector<Touch*>& touches, Event * event)
{
}

void JumpControlButton::onTouchesEnded(const std::vector<Touch*>& touches, Event * event)
{
}

void ControlBox::bindPlayer(Player * player)
{
	m_player = player;
}

void ControlBox::bindSprite(cocos2d::Sprite* sprite)
{
	m_sprite = sprite;
	this->addChild(m_sprite);
}
