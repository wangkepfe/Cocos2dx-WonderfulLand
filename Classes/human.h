#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "entity.h"

enum MoveMode {
	WALK_RIGHT,
	WALK_LEFT,
	STAND,
	BLINK,
	BREATHE
};

enum JumpMode {
	JUMP,
	FLY,
	FALL
};

class Human : public Entity
{
public:
	Human();
	~Human();

	virtual void setTagPosition(float x, float y);
	void setTiledMap(cocos2d::TMXTiledMap* map);
	void setMapMeta();

	void spriteUpdate(float dt);
	void moveUpdate();
	void bindSprite(cocostudio::Armature* armature);

	MoveMode moveMode, lastMoveMode;
	JumpMode jumpMode;
	
protected:
	cocos2d::TMXTiledMap* m_map;
	cocos2d::TMXLayer* meta, *semi_meta;
	cocostudio::Armature* m_sprite;
	float walkSpeed, jumpSpeed, gravity;
	int _layer;
	
	void moveLeft();
	void moveRight();
	void jump();
	void stand();
	void fallByGravity();

	cocos2d::Vec2 tileCoordForPosition(cocos2d::Vec2 pos);
	cocos2d::Vec2 positionForTileCoord(cocos2d::Vec2 coord);
private:
	float runPeriodTime;
	float spriteUpdateCount;
};

#endif