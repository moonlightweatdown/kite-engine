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
	//ControlLayer *controlLayer = ControlLayer::create();

	//��ControlLayerʵ����ӵ�������
	//this->addChild(controlLayer, kControlLayer, kControlLayer);

	return true;
}
