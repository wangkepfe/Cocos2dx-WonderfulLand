#include"ThinkButton.h"

USING_NS_CC;

bool ThinkButton::init()
{
	_label = Label::create();
	
	_label->setTTFConfig(ttfConfig);
	_menuItem = MenuItemLabel::create(_label);

	return true;
}

void ThinkButton::setFunction(ThinkButtonFunc func)
{
	_menuItem->setString("Enter The Room");
	_menuItem->setCallback([=](Ref* ref) {
		if (*m_layer == 0)
			*m_layer = 1;
	});
}

void ThinkButton::setLayer(int * layer)
{
	m_layer = layer;
}

cocos2d::MenuItemLabel * ThinkButton::getMenuItem()
{
	return _menuItem;
}


