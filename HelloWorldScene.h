#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
//#include"CardSprite.h"
#include "cocos2d.h"

USING_NS_CC;


class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	//void CreateCars(Ref * pSender, ui::Widget::TouchEventType type);
	//void update(float dt);
	//bool onTouchBegan(Touch * touch, Event * event);
	void initBoard();
	void initRoute();
	void initCar();
	void update(float dt);
	void showcar();
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

struct S
{
	int x, y;
	S() :x(-1), y(-1) {}
	S(int xx, int yy) :x(xx), y(yy) {}
	bool operator<(const S &s) const
	{
		if (s.x>x || (s.x == x&&s.y>y))return true;
		else return false;
	}
};

struct M
{
	int x, y;
	int CarNum;
	bool flag;
	M() :x(-1), y(-1), flag(false),CarNum(-1) {}
	M(int xx,int yy) :x(xx), y(yy),  flag(false),CarNum(-1) {}
};
#endif // __HELLOWORLD_SCENE_H__
