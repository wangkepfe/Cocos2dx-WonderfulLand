#include"ThinkMenu.h"

USING_NS_CC;

bool ThinkMenu::init()
{
	_menu = Menu::create();
	this->addChild(_menu);
	return true;
}

void ThinkMenu::addMenuItem(ThinkMenuFunc func)
{
	TTFConfig ttfConfig("fonts/Marker Felt.ttf", 50);
	auto _label = Label::create();
	_label->setTTFConfig(ttfConfig);
	_label->setCameraMask(2);
	_label->setColor(Color3B::BLACK);

	if (func == MENU_ENTER)
		_label->setString("Enter");
	else if (func == MENU_EXIT)
		_label->setString("Exit");

	_menuItem = MenuItemLabel::create(_label, [=](Ref* ref) {
		if (func == MENU_ENTER)
		{
			if (*m_layer <= 1)
				(*m_layer)++;
		}
		else if (func == MENU_EXIT)
		{
			if (*m_layer >= 0)
				(*m_layer)--;
		}
	});
	_menuItem->setCameraMask(2);
	Size size = Director::getInstance()->getWinSize();
	_menuItem->setPosition(-0.5f * size.width, -0.5f * size.height);
	_menu->addChild(_menuItem);
	_menuItem->setOpacity(0);
	_menuItem->runAction(Spawn::create(MoveBy::create(.5f, Vec2(0, 150.f)), FadeIn::create(.5f), nullptr));
}

void ThinkMenu::removeMenuItem()
{
	_menuItem->runAction(Sequence::create(DelayTime::create(.5f), CallFunc::create([=](){
		_menuItem->stopAllActions();
		_menuItem->removeFromParent();
	}),nullptr));
	_menuItem->runAction(FadeOut::create(.5f));
}

void ThinkMenu::setLayer(int * layer)
{
	m_layer = layer;
}




