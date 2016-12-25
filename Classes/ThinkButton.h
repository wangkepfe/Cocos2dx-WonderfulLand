#ifndef __THINK_BUTTON_H__
#define __THINK_BUTTON_H__

#include "cocos2d.h"

enum ThinkButtonFunc {
	BUTTON_ENTER,
	BUTTON_EXIT
};

class ThinkButton : public cocos2d::Node
{
public:
	ThinkButton() {};
	~ThinkButton() {};
	CREATE_FUNC(ThinkButton);
	virtual bool init();
	void setFunction(ThinkButtonFunc func);
	void setLayer(int *layer);
	cocos2d::MenuItemLabel* getMenuItem();
private:
	int *m_layer;
	cocos2d::Label *_label;
	cocos2d::MenuItemLabel *_menuItem;
};

#endif