#pragma once
#include "cocos2d.h"
#include "HelloWorldScene.h"

class CardSprite :public cocos2d::Layer
{
	//friend class HelloWorld;
public:
	int direction[4];//记录道路方向属性
	char type;//'r'为路，'w'为墙，'p'为停车位
	cocos2d::Sprite* card;
	std::queue<S>route_in, route_out;
	CardSprite();
	static CardSprite* createCardSprite(int type, float x, float y);//创建图块
	void cardInit(int type, float x, float y);//图块初始化
	virtual bool init();
	CREATE_FUNC(CardSprite);
};