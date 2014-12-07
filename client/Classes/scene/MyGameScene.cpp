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
	//�½�һ��GameLayerʵ��
	MyGameLayer *mygamelayer = MyGameLayer::create();

	//��GameLayerʵ����ӵ�������
	this->addChild(mygamelayer, 0, 0);

	//�½�һ��ControlLayerʵ��
	MyControlLayer *MycontrolLayer =MyControlLayer::create();

	//��ControlLayerʵ����ӵ�������
	this->addChild(MycontrolLayer, kControlLayer, kControlLayer);

	return true;
}
//�л���Ϸ��ͼ֮ǰ
void MyGameScene::switchMap()
{
	//����һ�����ֲ㣬���ڵ�ͼ�л�ʱ����ʾ���뵭��Ч��
	LayerColor* fadeLayer = LayerColor::create(Color4B(0, 0, 0, 0));

	fadeLayer->setAnchorPoint(Point::ZERO);
	fadeLayer->setPosition(Point::ZERO);
	addChild(fadeLayer, kFadeLayer, kFadeLayer);

	//ִ�е��붯�������������resetGameLayer����
	Action* action = Sequence::create(
		FadeIn::create(0.5f), 
		CallFunc::create(CC_CALLBACK_0(MyGameScene::resetGameLayer, this)), 
		NULL);

	fadeLayer->runAction(action);
}

//�л���Ϸ��ͼ
void MyGameScene::resetGameLayer()
{
	//ɾ���ϵ�GameLayer
	this->removeChildByTag(kGameLayer, true);

	//�����µ�GameLayer
	MyGameLayer *gamelayer = MyGameLayer::create();
	this->addChild(gamelayer, kGameLayer, kGameLayer);

	//���ֲ�ִ�е���Ч���������󣬵���removeFadeLayer����ɾ�����ֲ�
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
