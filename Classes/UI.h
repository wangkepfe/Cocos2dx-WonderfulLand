#ifndef __UI_H__
#define __UI_H__

#include "cocos2d.h"
#include "player.h"

class ControlBox : public cocos2d::Layer
{
public:
	ControlBox() {};
	~ControlBox() {};

	void bindSprite(cocos2d::Sprite* sprite);
	void bindPlayer(Player* player);
protected:
	Player* m_player;
	cocos2d::Sprite* m_sprite; 
};

class WalkControlButton : public ControlBox
{
public:
	WalkControlButton() {};
	~WalkControlButton() {};

	CREATE_FUNC(WalkControlButton);
	virtual bool init();

	virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);

private:
	bool onPress;
};

class JumpControlButton : public ControlBox
{
public:
	JumpControlButton() {};
	~JumpControlButton() {};

	CREATE_FUNC(JumpControlButton);
	virtual bool init();

	virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);

private:
};


#endif
