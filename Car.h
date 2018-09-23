#pragma once
#include "cocos2d.h"
#include "HelloWorldScene.h"

class Car :public cocos2d::Layer
{
	//friend class HelloWorld;

public:
	int CarNum;
	int OnRuning;//0Ϊֹͣ״̬��1Ϊ�˶�״̬��2Ϊ������λ״̬
	int x, y, time_in, time_out, park_in, park_out;
	int type;//0Ϊ��⳵��1Ϊ���⳵
	std::queue<S>route_in, route_out;
	cocos2d::Sprite* car;
	Car();
	Car(int carnum, int onruning, int xx, int yy, int tt);
	static Car* createCarSprite(int num,int x,int y);//����ͼ��
	void carInit(int num, int x, int y);//ͼ���ʼ��
	virtual bool init();
	CREATE_FUNC(Car);
};