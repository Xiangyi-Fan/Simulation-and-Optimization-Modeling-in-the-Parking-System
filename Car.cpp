#include"Car.h"
#include"HelloWorldScene.h"

Car::Car() 
{
	OnRuning = 0;
	CarNum = -1;
	x = 1;
	y = 0;
	type = 0;
	car = new cocos2d::Sprite();
}

Car::Car(int carnum,int onruning,int xx,int yy,int tt) {
	OnRuning = onruning;
	CarNum = carnum;
	x = xx;
	y = yy;
	type = tt;
	car = new cocos2d::Sprite();
}

Car* Car::createCarSprite(int num,int x,int y)
{
	Car* car = new Car();
	if (car&&car->init()) {
		car->autorelease();
		car->carInit(num, x, y);
		return car;
	}
	CC_SAFE_DELETE(car);
	return NULL;
}

bool Car::init()
{
	if (!Layer::init())return false;
	return true;
}

void Car::carInit(int num,int x,int y)
{
	this->x = x;
	this->y = y;
	this->CarNum = num;
	car = cocos2d::Sprite::create("car.png");
	car->setPosition(85 + 11 * x, 163 + 297 + 11 * y);
	addChild(car);
}

/* operator<(const Car &s1, const Car &s2)const
{
	if (s1.time_out>s2.time_out || (s1.time_out == s2.time_out&&s1.time_in > s2.time_in))return true;
	else return false;
}*/

