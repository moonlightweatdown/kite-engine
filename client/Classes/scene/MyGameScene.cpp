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
	//ControlLayer *controlLayer = ControlLayer::create();

	//将ControlLayer实例添加到场景中
	//this->addChild(controlLayer, kControlLayer, kControlLayer);

	return true;
}
