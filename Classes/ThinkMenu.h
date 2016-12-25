#ifndef __THINK_MENU_H__
#define __THINK_MENU_H__

#include "cocos2d.h"

enum ThinkMenuFunc {
	MENU_ENTER,
	MENU_EXIT
};

class ThinkMenu : public cocos2d::Node
{
public:
	ThinkMenu() {};
	~ThinkMenu() {};
	CREATE_FUNC(ThinkMenu);
	virtual bool init();

	void addMenuItem(ThinkMenuFunc func);
	void removeMenuItem();
	void setLayer(int *layer);
private:
	int *m_layer;
	cocos2d::Menu *_menu;
	cocos2d::MenuItemLabel *_menuItem;
};


#endif // !__THINK_MENU__
