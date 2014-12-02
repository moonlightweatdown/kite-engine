#include "GameScene.h"

GameScene::GameScene(void)
{
	sGlobal->gameScene = this;
}

GameScene::~GameScene(void)
{
}

bool GameScene::init()
{
	//新建一个GameLayer实例
	GameLayer *gamelayer = GameLayer::create();

	//将GameLayer实例添加到场景中
	this->addChild(gamelayer, kGameLayer, kGameLayer);

	//新建一个ControlLayer实例
	ControlLayer *controlLayer = ControlLayer::create();

	//将ControlLayer实例添加到场景中
	this->addChild(controlLayer, kControlLayer, kControlLayer);

	return true;
}

//切换游戏地图之前
void GameScene::switchMap()
{
	//创建一个遮罩层，用于地图切换时的显示淡入淡出效果
	LayerColor* fadeLayer = LayerColor::create(Color4B(0, 0, 0, 0));

	fadeLayer->setAnchorPoint(Point::ZERO);
	fadeLayer->setPosition(Point::ZERO);
	addChild(fadeLayer, kFadeLayer, kFadeLayer);

	//执行淡入动画，结束后调用resetGameLayer方法
	Action* action = Sequence::create(
		FadeIn::create(0.5f), 
		CallFunc::create(CC_CALLBACK_0(GameScene::resetGameLayer, this)), 
		NULL);

	fadeLayer->runAction(action);
}

//切换游戏地图
void GameScene::resetGameLayer()
{
	//删除老的GameLayer
	this->removeChildByTag(kGameLayer, true);

	//创建新的GameLayer
	GameLayer *gamelayer = GameLayer::create();
	this->addChild(gamelayer, kGameLayer, kGameLayer);

	//遮罩层执行淡出效果，结束后，调用removeFadeLayer方法删除遮罩层
	Action* action = Sequence::create(
		FadeOut::create(0.5f), 
		CallFunc::create(CC_CALLBACK_0(GameScene::removeFadeLayer, this)),	
		NULL);

	this->getChildByTag(kFadeLayer)->runAction(action);
}

void GameScene::removeFadeLayer()
{
	this->removeChildByTag(kFadeLayer, true);
}