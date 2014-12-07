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

	//创建关闭按钮
	MenuItemImage *pCloseItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(MyControlLayer::menuCloseCallback));
	pCloseItem->setPosition(Point(Director::getInstance()->getWinSize().width - 20, 20));
	
	Menu* pMenu = Menu::create(pCloseItem, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu, 1);

	//创建方向按钮
	MenuItem *down = MenuItemFont::create("down", this, menu_selector(MyControlLayer::menuCallBackMove));
	MenuItem *left = MenuItemFont::create("left", this, menu_selector(MyControlLayer::menuCallBackMove) );
	MenuItem *right = MenuItemFont::create("right", this, menu_selector(MyControlLayer::menuCallBackMove) );
	MenuItem *up = MenuItemFont::create("up", this, menu_selector(MyControlLayer::menuCallBackMove) );
	Menu* menu = Menu::create(down, left, right, up, NULL);
	
	//为了方便查找，给每个menuItem设置tag
	down->setTag(kDown);
	left->setTag(kLeft);
	right->setTag(kRight);
	up->setTag(kUp);
	
	//菜单项按间距50水平排列
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

	//按钮的tag就是需要行走的方向
	int targetDirection = node->getTag();

	MysGlobal->Myhero->move((HeroDirection) targetDirection);
}