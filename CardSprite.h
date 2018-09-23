#pragma once
#include "cocos2d.h"
#include "HelloWorldScene.h"

class CardSprite :public cocos2d::Layer
{
	//friend class HelloWorld;
public:
	int direction[4];//��¼��·��������
	char type;//'r'Ϊ·��'w'Ϊǽ��'p'Ϊͣ��λ
	cocos2d::Sprite* card;
	std::queue<S>route_in, route_out;
	CardSprite();
	static CardSprite* createCardSprite(int type, float x, float y);//����ͼ��
	void cardInit(int type, float x, float y);//ͼ���ʼ��
	virtual bool init();
	CREATE_FUNC(CardSprite);
};