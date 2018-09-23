#pragma once
#include "cocos2d.h"
#include "HelloWorldScene.h"

class Car :public cocos2d::Layer
{
	//friend class HelloWorld;

public:
	int CarNum;
	int OnRuning;//0为停止状态，1为运动状态，2为调整车位状态
	int x, y, time_in, time_out, park_in, park_out;
	int type;//0为入库车，1为出库车
	std::queue<S>route_in, route_out;
	cocos2d::Sprite* car;
	Car();
	Car(int carnum, int onruning, int xx, int yy, int tt);
	static Car* createCarSprite(int num,int x,int y);//创建图块
	void carInit(int num, int x, int y);//图块初始化
	virtual bool init();
	CREATE_FUNC(Car);
};