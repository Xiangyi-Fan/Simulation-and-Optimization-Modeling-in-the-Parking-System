#include"CardSprite.h"
#include"HelloWorldScene.h"

CardSprite::CardSprite() {
	type = '\0';
	for (int i = 0; i < 4; ++i)direction[i] = 0;
	card = new cocos2d::Sprite();
}

//创建图块
CardSprite* CardSprite::createCardSprite(int type, float x, float y)
{
	CardSprite* card = new CardSprite();
	if (card&&card->init()) {
		card->autorelease();
		card->cardInit(type, x, y);
		return card;
	}
	CC_SAFE_DELETE(card);
	return NULL;
}

bool CardSprite::init()
{
	if (!Layer::init())return false;
	return true;
}

//图块初始化
void CardSprite::cardInit(int type, float x, float y)
{
	switch (type) {
	case 1:this->type = 'w'; break;
	case 2: {
		this->type = 'r';
		this->direction[0] = 1;
		break;
	}
	case 3: {
		this->type = 'r';
		this->direction[1] = 1;
		break;
	}
	case 4: {
		this->type = 'r';
		this->direction[2] = 1;
		break;
	}
	case 5: {
		this->type = 'r';
		this->direction[3] = 1;
		break;
	}
	case 6:this->type = 'r'; break;
	case 7:this->type = 'p'; break;
	case 8:this->type = 'e'; break;
	}
	card->setAnchorPoint(Vec2(0, 0));
	/*if (this->type == 'r') {
		card = cocos2d::Sprite::create("road.jpg");
		card->setPosition(85 + 11 * x, 481 - 11 * y);
		addChild(card);
	}
	else if (this->type == 'p') {
		card = cocos2d::Sprite::create("parking.png");
		card->setPosition(85 + 11 * x, 481 - 11 * y);
		addChild(card);
	}
	else if (this->type == 'w') {
		card = cocos2d::Sprite::create("wall.jpg");
		card->setPosition(85 + 11 * x, 481 - 11 * y);
		addChild(card);
	}*/
	if (this->type == 'r') {
		card = cocos2d::Sprite::create(cocos2d::String::createWithFormat("road%d.png", type)->getCString());
		card->setPosition(85 + 11 * x, 481 - 11 * y);
		addChild(card);
	}
	else if (this->type == 'p') {
		card = cocos2d::Sprite::create("parking.png");
		card->setPosition(85 + 11 * x, 481 - 11 * y);
		addChild(card);
	}
	else if (this->type == 'w') {
		card = cocos2d::Sprite::create("wall.jpg");
		card->setPosition(85 + 11 * x, 481 - 11 * y);
		addChild(card);
	}
	else if (this->type == 'e') {
		card = cocos2d::Sprite::create("park_in&out.png");
		card->setPosition(85 + 11 * x, 481 - 11 * y);
		addChild(card);
	}
}