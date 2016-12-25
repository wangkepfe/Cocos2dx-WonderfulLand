#include "human.h"

USING_NS_CC;

Human::Human()
{
	m_map = NULL;
	spriteUpdateCount = 0;
	runPeriodTime = 0;
}

Human::~Human()
{
	CC_SAFE_RELEASE(m_map);
}

void Human::spriteUpdate(float dt)
{
	if (moveMode == STAND)// blink when stand
	{
		spriteUpdateCount += dt;
		if (spriteUpdateCount >= 8.f)
		{
			moveMode = BLINK;
			spriteUpdateCount = 0;
		}
	}

	if (moveMode == BLINK)// blink for short time, then be normal
	{
		spriteUpdateCount += dt;
		if (spriteUpdateCount >= 0.3f)
		{
			moveMode = STAND;
			spriteUpdateCount = 0;
		}
	}

	if (moveMode == BREATHE)// breathing for some time, then be normal
	{
		spriteUpdateCount += dt;
		if (spriteUpdateCount >= 1.8f)
		{
			moveMode = STAND;
			spriteUpdateCount = 0;
		}
	}

	if (moveMode == WALK_RIGHT || moveMode == WALK_LEFT) //record the time period during running
	{
		runPeriodTime += dt;
	}

	if (lastMoveMode != moveMode)
	{
		// walk for a long time, then breathe
		if ((lastMoveMode == WALK_RIGHT || lastMoveMode == WALK_LEFT) 
			&& (moveMode != WALK_RIGHT || moveMode != WALK_LEFT)
			&& runPeriodTime > 5)
		{
			runPeriodTime = 0;
			spriteUpdateCount = 0;
			moveMode = BREATHE;
		}

		switch (moveMode)
		{
		case WALK_RIGHT:
			m_sprite->getAnimation()->playWithIndex(0);
			m_sprite->setRotationY(180);
			break;
		case WALK_LEFT:
			m_sprite->getAnimation()->playWithIndex(0);
			m_sprite->setRotationY(0);
			break;
		case STAND:
			m_sprite->getAnimation()->playWithIndex(3);
			runPeriodTime = 0;
			break;
		case BLINK:
			m_sprite->getAnimation()->playWithIndex(1);
			break;
		case BREATHE:
			m_sprite->getAnimation()->playWithIndex(2);
			break;
		default:
			break;
		}
		lastMoveMode = moveMode;
	}
}

void Human::moveUpdate()
{
	switch (moveMode)
	{
	case WALK_RIGHT:	moveRight();
		break;
	case WALK_LEFT: 	moveLeft();
		break;
	case STAND: stand();
		break;
	default: stand();
		break;
	}

	switch (jumpMode)
	{
	case JUMP: jump(); jumpMode = FALL;
		break;
	case FLY: fallByGravity();
		break;
	case FALL: fallByGravity();
		break;
	default: fallByGravity();
		break;
	}
}

void Human::bindSprite(cocostudio::Armature* armature)
{
	m_sprite = armature;
	m_sprite->setPositionY(10);
	this->addChild(m_sprite);
}

void Human::setTagPosition(float x, float y)
{
	setPosition(x, y);
}

void Human::moveLeft()
{
	auto pos = getPosition();
//	auto size = m_sprite->getContentSize();
	auto size = Size(100, 200);

	cocos2d::Vec2 tilePos[3];
	int tileGrid[3];

	tilePos[0] = tileCoordForPosition(cocos2d::Vec2(pos.x + size.width * 0.5f - 1, pos.y - 5));
	tilePos[1] = tileCoordForPosition(cocos2d::Vec2(pos.x + size.width * 0.5f - 1, pos.y - size.height / 2));
	tilePos[2] = tileCoordForPosition(cocos2d::Vec2(pos.x + size.width * 0.5f - 1, pos.y - size.height + 5));

	for (int i = 0; i < 3; i++)
	{
		tileGrid[i] = meta->tileGIDAt(tilePos[i]);
		if (tileGrid[i] != 0)
		{
			setPositionX(positionForTileCoord(cocos2d::Vec2(tilePos[0].x + 0.5f, tilePos[0].y)).x);
			moveMode = STAND;
			return;
		}
	}

	m_controller->setiSpeedX(-walkSpeed);
}

void Human::moveRight()
{
	auto pos = getPosition();
	//auto size = m_sprite->getContentSize();
	auto size = Size(100, 200);

	cocos2d::Vec2 tilePos[3];
	int tileGrid[3];

	tilePos[0] = tileCoordForPosition(cocos2d::Vec2(pos.x + size.width * 1.5f + 1, pos.y - size.height + 5));
	tilePos[1] = tileCoordForPosition(cocos2d::Vec2(pos.x + size.width * 1.5f + 1, pos.y - size.height / 2));
	tilePos[2] = tileCoordForPosition(cocos2d::Vec2(pos.x + size.width * 1.5f + 1, pos.y - 5));

	for (int i = 0; i < 3; i++)
	{
		tileGrid[i] = meta->tileGIDAt(tilePos[i]);
		if (tileGrid[i] != 0)
		{
			setPositionX(positionForTileCoord(cocos2d::Vec2(tilePos[0].x - 1.5f, tilePos[0].y)).x);
			moveMode = STAND;
			return;
		}
	}

	m_controller->setiSpeedX(walkSpeed);
}

void Human::jump()
{
	m_controller->setiSpeedY(jumpSpeed);
}

void Human::stand()
{
	m_controller->setiSpeedX(0);
}

void Human::fallByGravity()
{
	auto pos = getPosition();
	auto tileSize = m_map->getTileSize();
	//auto size = m_sprite->getContentSize();
	auto size = Size(100, 200);

	cocos2d::Vec2 tilePos[2];
	int tileGrid[2];

	tilePos[0] = tileCoordForPosition(cocos2d::Vec2(pos.x + size.width / 2 + 10, pos.y - size.height - 1));
	tilePos[1] = tileCoordForPosition(cocos2d::Vec2(pos.x + size.width * 3 / 2 - 10, pos.y - size.height - 1));

	for (int i = 0; i < 2; i++)
	{
		tileGrid[i] = meta->tileGIDAt(tilePos[i]);
		if (tileGrid[i] != 0)
		{
			setPositionY(positionForTileCoord(cocos2d::Vec2(tilePos[0].x, tilePos[0].y - 2)).y);
			m_controller->setiSpeedY(0);
			return;
		}

		tileGrid[i] = semi_meta->tileGIDAt(tilePos[i]);
		if (tileGrid[i] != 0 && 
			m_controller->getiSpeed().y < 0 &&
			((int)(pos.y - size.height) % (int)(tileSize.height) > (int)(tileSize.height * 0.7f)))
		{
			setPositionY(positionForTileCoord(cocos2d::Vec2(tilePos[0].x, tilePos[0].y - 2)).y);
			m_controller->setiSpeedY(0);
			return;
		}
	}

	tilePos[0] = tileCoordForPosition(cocos2d::Vec2(pos.x + size.width / 2 + 10, pos.y - 1));
	tilePos[1] = tileCoordForPosition(cocos2d::Vec2(pos.x + size.width * 3 / 2 - 10, pos.y - 1));

	for (int i = 0; i < 2; i++)
	{
		tileGrid[i] = meta->tileGIDAt(tilePos[i]);
		if (tileGrid[i] != 0)
		{
			setPositionY(positionForTileCoord(cocos2d::Vec2(tilePos[0].x, tilePos[0].y + 1)).y);
			m_controller->setiSpeedY(0);
			return;
		}
	}

	m_controller->setAccelerateY(gravity);
}

cocos2d::Vec2 Human::tileCoordForPosition(cocos2d::Vec2 pos)
{
	auto tileSize = m_map->getTileSize();
	auto mapSize = m_map->getMapSize();
	int x = pos.x / tileSize.width;
	int y = (mapSize.height * tileSize.height - pos.y) / tileSize.height;
	if (x > 0)
		x--;
	if (y > 0)
		y--;
	return cocos2d::Vec2(x, y);
}

cocos2d::Vec2 Human::positionForTileCoord(cocos2d::Vec2 coord)
{
	auto tileSize = m_map->getTileSize();
	auto mapSize = m_map->getMapSize();
	coord.x++;
	coord.y++;
	float x = coord.x * tileSize.width;
	float y = mapSize.height * tileSize.height - coord.y * tileSize.height;
	return cocos2d::Vec2(x, y);
}

void Human::setTiledMap(cocos2d::TMXTiledMap * map)
{
	CC_SAFE_RETAIN(map);
	CC_SAFE_RELEASE(m_map);
	m_map = map;

	setMapMeta();
}

void Human::setMapMeta()
{
	switch (_layer)
	{
	case 0: meta = m_map->getLayer("meta0");
			semi_meta = m_map->getLayer("semi_meta0");
		break;
	case 1: meta = m_map->getLayer("meta1");
			semi_meta = m_map->getLayer("semi_meta1");
		break;
	case 2: meta = m_map->getLayer("meta2");
			semi_meta = m_map->getLayer("semi_meta2");
		break;
	default: meta = m_map->getLayer("meta0");
			semi_meta = m_map->getLayer("semi_meta0");
		break;
	}
	meta->retain();
}
