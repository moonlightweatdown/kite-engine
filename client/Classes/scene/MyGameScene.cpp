#include "MyGameScene.h"

MyGameScene::MyGameScene(void)
{
	 MysGlobal->MygameScene = this;
}

MyGameScene::~MyGameScene(void)
{
}

bool MyGameScene::init()
{
	//新建一个GameLayer实例
	MyGameLayer *mygamelayer = MyGameLayer::create();

	//将GameLayer实例添加到场景中
	this->addChild(mygamelayer, 0, 0);

	//新建一个ControlLayer实例
	MyControlLayer *MycontrolLayer =MyControlLayer::create();

	//将ControlLayer实例添加到场景中
	this->addChild(MycontrolLayer, kControlLayer, kControlLayer);

	return true;
}
//切换游戏地图之前
void MyGameScene::switchMap()
{
	//创建一个遮罩层，用于地图切换时的显示淡入淡出效果
	LayerColor* fadeLayer = LayerColor::create(Color4B(0, 0, 0, 0));

	fadeLayer->setAnchorPoint(Point::ZERO);
	fadeLayer->setPosition(Point::ZERO);
	addChild(fadeLayer, kFadeLayer, kFadeLayer);

	//执行淡入动画，结束后调用resetGameLayer方法
	Action* action = Sequence::create(
		FadeIn::create(0.5f), 
		CallFunc::create(CC_CALLBACK_0(MyGameScene::resetGameLayer, this)), 
		NULL);

	fadeLayer->runAction(action);
}

//切换游戏地图
void MyGameScene::resetGameLayer()
{
	//删除老的GameLayer
	this->removeChildByTag(kGameLayer, true);

	//创建新的GameLayer
	MyGameLayer *gamelayer = MyGameLayer::create();
	this->addChild(gamelayer, kGameLayer, kGameLayer);

	//遮罩层执行淡出效果，结束后，调用removeFadeLayer方法删除遮罩层
	Action* action = Sequence::create(
		FadeOut::create(0.5f), 
		CallFunc::create(CC_CALLBACK_0(MyGameScene::removeFadeLayer, this)),	
		NULL);

	this->getChildByTag(kFadeLayer)->runAction(action);
}

void MyGameScene::removeFadeLayer()
{
	this->removeChildByTag(kFadeLayer, true);
}
