#include"player.h"

USING_NS_CC;

bool Player::init()
{
	moveMode = STAND;
	lastMoveMode = STAND;
	jumpMode = FALL;
	cameraPosition = BOTTOM_CENTER;

	walkSpeed = 3.f;
	jumpSpeed = 5.f;
	gravity = -0.1f;

	last_layer = 0;
	_layer = 0;
	inEvent = 0;

	m_menu = ThinkMenu::create();
	m_menu->setLayer(&_layer);
	m_menu->setCameraMask(2);
	this->addChild(m_menu,6);

	loadEvents();

	this->scheduleUpdate();
	return true;
}

void Player::update(float dt)
{
	moveUpdate();
	spriteUpdate(dt);

	setCameraPosition();
	moveCameraPosition();

	eventUpdate(dt);
}

void Player::setCamera(cocos2d::Camera* camera)
{
	m_camera = camera;
}

void Player::moveCameraPosition()
{
	Size size = Director::getInstance()->getWinSize();
	Vec2 destination = getPosition();
	switch (cameraPosition)
	{
	case BOTTOM_CENTER:
		destination = destination - Vec2(size.width * 0.5f, size.height * 0.286f);
		m_camera->setPosition(destination);
		break;
	case BOTTOM_RIGHT:
		break;
	case BOTTOM_LEFT:
		break;
	case CENTER:
		break;
	case STILL:
		break;
	default:
		break;
	}
}

void Player::setCameraPosition()
{
	cameraPosition = BOTTOM_CENTER;
}

void Player::eventUpdate(float dt)
{
	//on scene change
	if (last_layer != _layer)
	{
		sceneTransform();

		inEvent = 2;
		timeCountEvent = 0;
		m_menu->removeMenuItem();

		loadEvents();

		last_layer = _layer;
	}
	//event triger
	eventTriger(dt);
}

void Player::loadEvents()
{
	if (_layer == 0)
	{
		myEventNum = 1;

		myEvent[0].objectGroupName = "door";
		myEvent[0].objectName = "door_outside";
		myEvent[0].menuFunc = MENU_ENTER;
	}
	else if (_layer == 1)
	{
		myEventNum = 4;

		myEvent[0].objectGroupName = "door";
		myEvent[0].objectName = "door_outside";
		myEvent[0].menuFunc = MENU_EXIT;

		myEvent[1].objectGroupName = "door";
		myEvent[1].objectName = "door_inside_1";
		myEvent[1].menuFunc = MENU_ENTER;
		 
		myEvent[2].objectGroupName = "door";
		myEvent[2].objectName = "door_inside_2";
		myEvent[2].menuFunc = MENU_ENTER;
		 
		myEvent[3].objectGroupName = "door";
		myEvent[3].objectName = "door_inside_3";
		myEvent[3].menuFunc = MENU_ENTER;

	}
	else if (_layer == 2)
	{
		myEventNum = 3;

		myEvent[0].objectGroupName = "door";
		myEvent[0].objectName = "door_inside_1";
		myEvent[0].menuFunc = MENU_EXIT;
		 
		myEvent[1].objectGroupName = "door";
		myEvent[1].objectName = "door_inside_2";
		myEvent[1].menuFunc = MENU_EXIT;
		 
		myEvent[2].objectGroupName = "door";
		myEvent[2].objectName = "door_inside_3";
		myEvent[2].menuFunc = MENU_EXIT;

	}
}

void Player::eventTriger(float dt)
{
	float x, y, x1, x2, y1, y2;

	bool inEventZone = 0;
	ThinkMenuFunc menuFunc;
	for (int i = 0; i < myEventNum; i++)
	{
		const std::string objectGroupName = myEvent[i].objectGroupName;
		const std::string objectName = myEvent[i].objectName;

		TMXObjectGroup* objGroup = m_map->getObjectGroup(objectGroupName);
		ValueMap playerPoint = objGroup->getObject(objectName);

		x1 = playerPoint["x"].asFloat();
		x2 = x1 + playerPoint["width"].asFloat();
		y1 = playerPoint["y"].asFloat();
		y2 = y1 + playerPoint["height"].asFloat();

		x = getPositionX();
		y = getPositionY();

		if (x < x2 && x > x1 && y < y2 && y > y1)
		{
			inEventZone = 1;
			menuFunc = myEvent[i].menuFunc;
			break;
		}
	}
	
	if (inEvent == 0)
	{
		if(inEventZone)
		{
			inEvent = 1;
			m_menu->addMenuItem(menuFunc);
		}
	}
	else if (inEvent == 1)
	{
		if (!inEventZone)
		{
			inEvent = 2;
			timeCountEvent = 0;
			m_menu->removeMenuItem();
		}
	}
	else
	{
		if (timeCountEvent > 2.f)
		{
			inEvent = 0;
		}
		else
		{
			timeCountEvent += dt;
		}
	}
}

void Player::sceneTransform()
{
	if ((last_layer == 0 && _layer == 1) || (last_layer == 1 && _layer == 0))
	{
		setMapMeta();

		TMXLayer *layer[4];
		layer[0] = m_map->getLayer("layer_outside_base_11");
		layer[1] = m_map->getLayer("layer_outside_base_21");
		layer[2] = m_map->getLayer("layer_outside_base_12");
		layer[3] = m_map->getLayer("layer_outside_decoration_11");

		TMXObjectGroup* objGroup = m_map->getObjectGroup("room");
		ValueMap playerPoint = objGroup->getObject("room1");

		float x1 = playerPoint["x"].asFloat();
		float x2 = x1 + playerPoint["width"].asFloat();
		float y1 = playerPoint["y"].asFloat();
		float y2 = y1 + playerPoint["height"].asFloat();

		auto point1 = tileCoordForPosition(Vec2(x1, y1));
		auto point2 = tileCoordForPosition(Vec2(x2, y2));

		for (int i = 0; i < 4; i++)
		{
			for (int j = point1.x + 1; j <= point2.x; j++)
			{
				for (int k = point2.y + 1; k <= point1.y; k++)
				{
					auto sprite = layer[i]->getTileAt(Vec2(j, k));
					if (sprite != nullptr)
					{
						if(last_layer == 0 && _layer == 1)
							sprite->runAction(FadeOut::create(1.f));
						else
							sprite->runAction(FadeIn::create(1.f));
					}
				}
			}
		}
	}
	else if ((last_layer == 1 && _layer == 2) || (last_layer == 2 && _layer == 1))
	{
		setMapMeta();

		TMXLayer *layer[3];
		layer[0] = m_map->getLayer("layer_1st_base_11");
		layer[1] = m_map->getLayer("layer_1st_base_21");
		layer[2] = m_map->getLayer("layer_1st_base_12");

		TMXObjectGroup* objGroup = m_map->getObjectGroup("room");
		ValueMap playerPoint = objGroup->getObject("room1");

		float x1 = playerPoint["x"].asFloat();
		float x2 = x1 + playerPoint["width"].asFloat();
		float y1 = playerPoint["y"].asFloat();
		float y2 = y1 + playerPoint["height"].asFloat();

		auto point1 = tileCoordForPosition(Vec2(x1, y1));
		auto point2 = tileCoordForPosition(Vec2(x2, y2));

		for (int i = 0; i < 3; i++)
		{
			for (int j = point1.x + 1; j <= point2.x; j++)
			{
				for (int k = point2.y + 1; k <= point1.y; k++)
				{
					auto sprite = layer[i]->getTileAt(Vec2(j, k));
					if (sprite != nullptr)
					{
						if (last_layer == 1 && _layer == 2)
							sprite->runAction(FadeOut::create(1.f));
						else
							sprite->runAction(FadeIn::create(1.f));
					}
				}
			}
		}
	}
}



