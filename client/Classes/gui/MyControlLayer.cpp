#include "MHGame.h"

MyControlLayer::MyControlLayer(void)
{
	MysGlobal->MycontrolLayer = this;
}

MyControlLayer::~MyControlLayer(void)
{

}

bool MyControlLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	//�����رհ�ť
	MenuItemImage *pCloseItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(MyControlLayer::menuCloseCallback));
	pCloseItem->setPosition(Point(Director::getInstance()->getWinSize().width - 20, 20));
	
	Menu* pMenu = Menu::create(pCloseItem, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu, 1);

	//��������ť
	MenuItem *down = MenuItemFont::create("down", this, menu_selector(MyControlLayer::menuCallBackMove));
	MenuItem *left = MenuItemFont::create("left", this, menu_selector(MyControlLayer::menuCallBackMove) );
	MenuItem *right = MenuItemFont::create("right", this, menu_selector(MyControlLayer::menuCallBackMove) );
	MenuItem *up = MenuItemFont::create("up", this, menu_selector(MyControlLayer::menuCallBackMove) );
	Menu* menu = Menu::create(down, left, right, up, NULL);
	
	//Ϊ�˷�����ң���ÿ��menuItem����tag
	down->setTag(kDown);
	left->setTag(kLeft);
	right->setTag(kRight);
	up->setTag(kUp);
	
	//�˵�����50ˮƽ����
	menu->alignItemsHorizontallyWithPadding(50);
	this->addChild(menu);
	return true;
}

void MyControlLayer::menuCloseCallback(cocos2d::Ref* pSender)
{
    Director::sharedDirector()->end();
}

void MyControlLayer::menuCallBackMove(cocos2d::Ref* pSender)
{
    Node *node = (Node *) pSender;

	//��ť��tag������Ҫ���ߵķ���
	int targetDirection = node->getTag();

	MysGlobal->Myhero->move((HeroDirection) targetDirection);
}