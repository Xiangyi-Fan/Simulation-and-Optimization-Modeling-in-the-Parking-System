#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include"CardSprite.h"
#include"Car.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<map>
//using namespace std;

USING_NS_CC;

using namespace cocostudio::timeline;

//std::vector<std::vector<CardSprite*>> cardSprite(30);
CardSprite* cardSprite[30][73];
TMXTiledMap* recMap;
Car* car[301];
int num[4] = {0,0,0,0};
std::vector<M>district[4];
std::vector<S>outer;
std::vector<std::vector<S>>outer_route[4];
int time1 = 0, outer_num[4] = {0,0,20,37};

//���³���ͣ�����
void HelloWorld::update(float dt)
{
	int car_start, car_end, park, park_in = 0;
	if (time1 <= 2000)++time1;
	for (int i = 1; i <= 30; ++i) {
		park_in = car[i]->park_in;
		car_start = -1; car_end = -1; park = -1;
		//������ʼ���
		if (time1 == car[i]->time_in) {
			if (car[i]->CarNum == 30) {
				auto exture = cocos2d::Director::getInstance()->getTextureCache()->addImage("car_out.png");
				auto frame = cocos2d::SpriteFrame::create("car_out.png", cocos2d::Rect(0, 0, 11, 11));//����frame������ʾ
				car[i]->car->setDisplayFrame(frame);
			}
			for (int park_in1 = 1; park_in1 <= 3; ++park_in1) {
				int Max = -1;
				//�Ҷ�β
				for (int j = 0; j < district[park_in1].size(); ++j)
					if (district[park_in1][j].flag == true) {
						car_end = j;
						break;
					}
				if (car_end == -1)car_end = 0;
				//�Ҷ���
				for (int j = car_end; j < district[park_in1].size(); ++j)
					if (district[park_in1][j].flag == false) {
						car_start = j - 1;
						break;
					}
				if (Max < district[park_in1].size() - (car_start - car_end + 1)) {
					Max = district[park_in1].size() - (car_start - car_end + 1);
					park_in = park_in1;
				}
			}
			car[i]->park_in = park_in;
			//�Ҷ�β
			for (int j = 0; j < district[park_in].size(); ++j)
				if (district[park_in][j].flag == true) {
					car_end = j;
					break;
				}
			if (car_end == -1)car_end = 0;
			//�Ҷ���
			for (int j = car_end; j < district[park_in].size(); ++j)
				if (district[park_in][j].flag == false) {
					car_start = j - 1;
					break;
				}
			//�ҳ�λ
			for (int j = car_end; j <= car_start;++j)
				if (car[district[park_in][j].CarNum]->time_out < car[i]->time_out) {
					park = j;
					break;
				}
			if (park == -1)park = car_start + 1;
			//������λ
			for (int j = car_start; j >= park; --j) {
				int carNum = district[park_in][j].CarNum;
				if (car[carNum]->OnRuning == 0) {//���������
					int park_x, park_y;//������λ����
					//�ֳ���Ŀ�공λ���� 
					park_x = district[park_in][j + 1].x;
					park_y = district[park_in][j + 1].y;
					//�޸ĳ����·��(�����ֳ���·���������·���У�
					do {
						S temp = car[carNum]->route_out.front();
						car[carNum]->route_in.push(temp);
						car[carNum]->route_out.pop();
					} while (car[carNum]->route_in.back().x != park_x || car[carNum]->route_in.back().y != park_y);
					car[carNum]->OnRuning = 2;
					//���³�λ��Ϣ
					district[park_in][j + 1].CarNum = district[park_in][j].CarNum;
					district[park_in][j + 1].flag = true;
				}
				if (car[carNum]->OnRuning == 1) {//�����������
					S now = S(car[carNum]->x, car[carNum]->y);//��ǰ��������
					int park_x,park_y;//������λ����
					//�ֳ���Ŀ�공λ���� 
					park_x = district[park_in][j + 1].x;
					park_y = district[park_in][j + 1].y;
					//�޸ĳ��������·��
					car[carNum]->route_in = cardSprite[park_x][park_y]->route_in;
					car[carNum]->route_out = cardSprite[park_x][park_y]->route_out;
					while (car[carNum]->route_in.front().x != now.x|| car[carNum]->route_in.front().y != now.y) car[carNum]->route_in.pop();
					//���³�λ��Ϣ
					district[park_in][j + 1].CarNum = district[park_in][j].CarNum;
					district[park_in][j + 1].flag = true;
				}
				if (car[carNum]->OnRuning == 2) {//�������ڵ�����λ
					int park_x, park_y;//������λ����
					//�ֳ���Ŀ�공λ���� 
					park_x = district[park_in][j + 1].x;
					park_y = district[park_in][j + 1].y;
					//�޸ĳ����·��(�����ֳ���·���������·���У�
					while (car[carNum]->route_in.back().x != park_x || car[carNum]->route_in.back().y != park_y) {
						S temp = car[carNum]->route_out.front();
						car[carNum]->route_in.push(temp);
						car[carNum]->route_out.pop();
					}
					//���³�λ��Ϣ
					district[park_in][j + 1].CarNum = district[park_in][j].CarNum;
					district[park_in][j + 1].flag = true;
				}
			}
			//���³�λ��Ϣ
			district[park_in][park].CarNum = car[i]->CarNum;
			district[park_in][park].flag = true;
			int park_x = district[park_in][park].x, park_y = district[park_in][park].y;
			//ȷ�����������·��
			car[i]->route_in = cardSprite[park_x][park_y]->route_in;
			car[i]->route_out = cardSprite[park_x][park_y]->route_out;
			//���³���״̬��λ��
			car[i]->OnRuning = 1;
			car[i]->x = car[i]->route_in.front().x;
			car[i]->y = car[i]->route_in.front().y;
			car[i]->route_in.pop();
			//��ʾ����λ��
			car[i]->setPosition(11 * car[i]->y, 11 - 11 * car[i]->x);
		}
		//������ʼ����
		else if (time1 == car[i]->time_out) {
			//�������ڵ�����λ
			if (!car[i]->route_in.empty()) {
				//���³�λ��Ϣ
				for (int j = 0; j < district[park_in].size(); ++j)
					if (district[park_in][j].x == car[i]->route_in.back().x&&district[park_in][j].y == car[i]->route_in.back().y) {
						district[park_in][j].flag = false;
						break;
					}
				//�޸ĳ���·��
				while (!car[i]->route_out.empty()) {
					S temp = car[i]->route_out.front();
					car[i]->route_in.push(temp);
					car[i]->route_out.pop();
				}
				car[i]->route_out = car[i]->route_in;
				while (!car[i]->route_in.empty())car[i]->route_in.pop();
			}
			else {
				//���³�λ��Ϣ
				for (int j = 0; j < district[park_in].size(); ++j)
					if (district[park_in][j].x == car[i]->x&&district[park_in][j].y == car[i]->y) {
						district[park_in][j].flag = false;
						break;
					}
			}
			//���³���״̬��λ��
			car[i]->OnRuning = 3;
			car[i]->x = car[i]->route_out.front().x;
			car[i]->y = car[i]->route_out.front().y;
			car[i]->route_out.pop();
			//���³���λ��
			car[i]->setPosition(11 * car[i]->y, 11 - 11 * car[i]->x);
			//ָ�����⳵λ��·��
			for (int j = 0; j < outer_route[park_in][outer_num[park_in]].size(); ++j)
				car[i]->route_out.push(outer_route[park_in][outer_num[park_in]][j]);
			outer_num[park_in] = outer_num[park_in] + 1;
		}
		//���������������ڵ�����λ
		else if (car[i]->OnRuning == 1 || car[i]->OnRuning == 2) {
			car[i]->x = car[i]->route_in.front().x;
			car[i]->y = car[i]->route_in.front().y;
			car[i]->route_in.pop();
			//�жϳ����Ƿ��Ѿ�ͣ�복λ
			if (car[i]->route_in.empty())car[i]->OnRuning = 0;
			//���³���λ��
			car[i]->setPosition(11 * car[i]->y, 11 - 11 * car[i]->x);
		}
		//�������ڳ���
		else if (car[i]->OnRuning == 3) {
			car[i]->x = car[i]->route_out.front().x;
			car[i]->y = car[i]->route_out.front().y;
			car[i]->route_out.pop();
			//�жϳ����Ƿ��Ѿ�����
			if (car[i]->route_out.empty())car[i]->OnRuning = 0;
			//���³���λ��
			car[i]->setPosition(11 * car[i]->y, 11 - 11 * car[i]->x);
		}
	}
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    /**  you can create scene with following comment code instead of using csb file.
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    **/
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);

	//������ͼƬ���볡����
	auto* background = Sprite::create("background33.jpg");
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(0, 0);
	addChild(background);

	//����Ƭ��ͼ���뵽������
	//recMap = TMXTiledMap::create("map.tmx");
	//recMap->setAnchorPoint(Vec2(0, 0));
	//recMap->setPosition(79, 157);
	//TMXLayer* recLayer;
	//recLayer = recMap->layerNamed("Layer1");//��ȡ��ͼ�еĲ�Layer1
	//addChild(recMap);

	initBoard();
	showcar();
	//initRoute();
	//initCar();
	//scheduleUpdate();
	//schedule(schedule_selector(HelloWorld::update), 0.1f);

    return true;
}
//���복���ͼ
void HelloWorld::initBoard()
{
	int i, j, id;
	auto* recMap = TMXTiledMap::create("map.tmx");
	TMXLayer* recLayer = recMap->layerNamed("Layer1");
	for (i = 0; i < 68; ++i)
		for (j = 0; j < 25; ++j) {
			cardSprite[j][i] = new CardSprite();
			int id= recLayer->tileGIDAt(Vec2(i, j));//��ȡ��ͼ��ĳ��ͼ���idֵ
			cardSprite[j][i] = CardSprite::createCardSprite(id, i, j);
			addChild(cardSprite[j][i]);
		}
	//cardSprite[1][13]->direction[1] = 1; cardSprite[1][13]->direction[3] = 1;
	//cardSprite[1][61]->direction[1] = 1; cardSprite[1][61]->direction[3] = 1;
	//cardSprite[23][71]->direction[1] = 1; cardSprite[23][71]->direction[2] = 1;
	//cardSprite[28][1]->direction[0] = 1; cardSprite[28][1]->direction[2] = 1;
}
//�����������·��
void HelloWorld::initRoute()
{
	std::string str;
	std::queue<S>t;
	std::ifstream fin;
	std::string fullPath;
	int k = 0;
	//����"park_route_out.txt"�е�·��
	fullPath = FileUtils::getInstance()->fullPathForFilename("park_route_out.txt");
	fin.open(fullPath);
	while (getline(fin, str)) {
		int x, y, sx, sy;
		int i = 1;
		while (!t.empty())t.pop();
		std::string s = "";
		++k;
		while (i < str.size()) {
			s = "";
			while (str[i] >= '0'&&str[i] <= '9') {
				s = s + str[i];
				++i;
			}
			x = atoi(s.c_str());
			++i;
			s = "";
			while (str[i] >= '0'&&str[i] <= '9') {
				s = s + str[i];
				++i;
			}
			y = atoi(s.c_str());
			t.push(S(x, y));
			i = i + 4;
		}
		while (!t.empty()) {
			S m = t.front();
			M mm = M(m.x, m.y);
			if (cardSprite[m.x][m.y]->type=='p')district[k].push_back(mm);
			t.pop();
			if (cardSprite[m.x][m.y]->type == 'p')cardSprite[m.x][m.y]->route_out = t;
		}
	}
	fin.close();
	//����"route_1_0.txt"�е�·��
	fullPath = FileUtils::getInstance()->fullPathForFilename("route_1_0.txt");
	fin.open(fullPath);
	while (getline(fin, str)) {
		int x, y, sx, sy;
		int i = 1;
		while (!t.empty())t.pop();
		std::string s = "";
		while (i < str.size()) {
			s = "";
			while (str[i] >= '0'&&str[i] <= '9') {
				s = s + str[i];
				++i;
			}
			x = atoi(s.c_str());
			++i;
			s = "";
			while (str[i] >= '0'&&str[i] <= '9') {
				s = s + str[i];
				++i;
			}
			y = atoi(s.c_str());
			t.push(S(x, y));
			i = i + 4;
		}
		t.pop();
		cardSprite[x][y]->route_in = t;
	}
	fin.close();
	//����"park_route_out_outer1.txt"�е�·��
	fullPath = FileUtils::getInstance()->fullPathForFilename("park_route_out_outer1.txt");
	fin.open(fullPath);
	while (getline(fin, str)) {
		int x, y, sx, sy;
		int i = 1;
		while (!t.empty())t.pop();
		std::string s = "";
		while (i < str.size()) {
			s = "";
			while (str[i] >= '0'&&str[i] <= '9') {
				s = s + str[i];
				++i;
			}
			x = atoi(s.c_str());
			++i;
			s = "";
			while (str[i] >= '0'&&str[i] <= '9') {
				s = s + str[i];
				++i;
			}
			y = atoi(s.c_str());
			t.push(S(x, y));
			i = i + 4;
		}
		std::vector<S>tt;
		while (!t.empty()) {
			S m = t.front();
			tt.push_back(m);
			t.pop();
		}
		outer_route[1].push_back(tt);
		outer.push_back(tt[tt.size() - 1]);
	}
	fin.close();
	//����"park_route_out_outer2.txt"�е�·��
	fullPath = FileUtils::getInstance()->fullPathForFilename("park_route_out_outer2.txt");
	fin.open(fullPath);
	while (getline(fin, str)) {
		int x, y, sx, sy;
		int i = 1;
		while (!t.empty())t.pop();
		std::string s = "";
		while (i < str.size()) {
			s = "";
			while (str[i] >= '0'&&str[i] <= '9') {
				s = s + str[i];
				++i;
			}
			x = atoi(s.c_str());
			++i;
			s = "";
			while (str[i] >= '0'&&str[i] <= '9') {
				s = s + str[i];
				++i;
			}
			y = atoi(s.c_str());
			t.push(S(x, y));
			i = i + 4;
		}
		std::vector<S>tt;
		while (!t.empty()) {
			S m = t.front();
			tt.push_back(m);
			t.pop();
		}
		outer_route[2].push_back(tt);
	}
	fin.close();
	//����"park_route_out_outer3.txt"�е�·��
	fullPath = FileUtils::getInstance()->fullPathForFilename("park_route_out_outer3.txt");
	fin.open(fullPath);
	while (getline(fin, str)) {
		int x, y, sx, sy;
		int i = 1;
		while (!t.empty())t.pop();
		std::string s = "";
		while (i < str.size()) {
			s = "";
			while (str[i] >= '0'&&str[i] <= '9') {
				s = s + str[i];
				++i;
			}
			x = atoi(s.c_str());
			++i;
			s = "";
			while (str[i] >= '0'&&str[i] <= '9') {
				s = s + str[i];
				++i;
			}
			y = atoi(s.c_str());
			t.push(S(x, y));
			i = i + 4;
		}
		std::vector<S>tt;
		while (!t.empty()) {
			S m = t.front();
			tt.push_back(m);
			t.pop();
		}
		outer_route[3].push_back(tt);
	}
	fin.close();
}
//���복����Ϣ
void HelloWorld::initCar()
{
	std::string str;
	std::vector<S>t;
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename("parking.txt");
	std::ifstream fin;
	fin.open(fullPath);
	while (getline(fin, str)) {
		int carNum, time_in, time_out, park_in, park_out;
		if (str.size() < 1)continue;
		int i = 0;
		std::string s = "";
		while (str[i] >= '0'&&str[i] <= '9') {
			s = s + str[i];
			++i;
		}
		carNum = atoi(s.c_str());
		++i;
		s = "";
		car[carNum] = new Car();
		car[carNum] = Car::createCarSprite(carNum, 0, 1);
		addChild(car[carNum]);

		while (str[i] >= '0'&&str[i] <= '9') {
			s = s + str[i];
			++i;
		}
		time_in = atoi(s.c_str());
		++i;
		s = "";

		while (str[i] >= '0'&&str[i] <= '9') {
			s = s + str[i];
			++i;
		}
		park_in = atoi(s.c_str());
		++i;
		s = "";

		while (str[i] >= '0'&&str[i] <= '9') {
			s = s + str[i];
			++i;
		}
		time_out = atoi(s.c_str());
		++i;
		s = "";

		while (str[i] >= '0'&&str[i] <= '9') {
			s = s + str[i];
			++i;
		}
		park_out = atoi(s.c_str());
		++i;
		s = "";
		car[carNum]->CarNum = carNum;
		car[carNum]->park_in = park_in;
		car[carNum]->park_out = park_out;
		car[carNum]->time_in = time_in;
		if (time_out <= 1000)car[carNum]->time_out = time_out;
		else car[carNum]->time_out = 1 << 30;
	}
	fin.close();
}

//����ģ��ͼƬ
void HelloWorld::showcar()
{
	/*car[1] = new Car();
	car[1] = Car::createCarSprite(1, 8, 10);
	car[1]->setPosition(11 * 0, 11 - 11 * 19);
	addChild(car[1]);
	car[2] = new Car();
	car[2] = Car::createCarSprite(1, 8, 10);
	car[2]->setPosition(11 * 0, 11 - 11 * 20);
	addChild(car[2]);
	car[3] = new Car();
	car[3] = Car::createCarSprite(1, 8, 10);
	car[3]->setPosition(11 * 0, 11 - 11 * 21);
	addChild(car[3]);
	car[4] = new Car();
	car[4] = Car::createCarSprite(1, 8, 10);
	car[4]->setPosition(11 * 0, 11 - 11 * 22);
	addChild(car[4]);
	car[5] = new Car();
	car[5] = Car::createCarSprite(1, 8, 10);
	car[5]->setPosition(11 * 1, 11 - 11 * 18);
	addChild(car[5]);
	car[6] = new Car();
	car[6] = Car::createCarSprite(1, 8, 10);
	car[6]->setPosition(11 * 2, 11 - 11 * 18);
	addChild(car[6]);
	car[7] = new Car();
	car[7] = Car::createCarSprite(1, 8, 10);
	car[7]->setPosition(11 * 3, 11 - 11 * 18);
	addChild(car[7]);
	car[8] = new Car();
	car[8] = Car::createCarSprite(1, 8, 10);
	car[8]->setPosition(11 * 4, 11 - 11 * 18);
	addChild(car[8]);*/
	bool flag[25][68];
	memset(flag, false, sizeof(flag));
	int n = 0;
	for (int i = 0; i < 300; ++i) {
		int x = random() % 68;
		int y = random() % 25;
		while (!((cardSprite[y][x]->type == 'p'&&n<50) || cardSprite[y][x]->type == 'r') && !flag[y][x]) {
			x = random() % 68;
			y = random() % 25;
		}
		if (cardSprite[y][x]->type == 'p')++n;
		flag[y][x] = true;
		car[i] = new Car();
		car[i] = Car::createCarSprite(i, 0, 0);
		car[i]->setPosition(11 * x, 22 - 11 * y);
		addChild(car[i]);
	}

}
