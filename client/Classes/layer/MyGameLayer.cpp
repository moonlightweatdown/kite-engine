#include "MyGameLayer.h"

MyGameLayer::MyGameLayer(void)
{
	MysGlobal->MygameLayer = this;
}

MyGameLayer::~MyGameLayer(void)
{
	this->unscheduleAllSelectors();
}

bool MyGameLayer::init()
{
	//����tmx��ͼ
	char temp[20];
	sprintf(temp, "%d.tmx", MysGlobal->currentLevel);

	map = MyGameMap::gameMapWithTMXFile("m.tmx");

	addChild(map, 1, 1);

	//����Hero��ľ�̬��������ʵ��
	myhero = MyHero::create();
	//����Hero����ʼλ��
	myhero->setPosition(map->positionForTileCoord(MysGlobal->heroSpawnTileCoord));
	addChild(myhero, kZHero, kZHero);

	schedule(schedule_selector(MyGameLayer::update));

	return true;
}
void MyGameLayer::update(float time)
{
	//�����ʿ��������״̬������Ҫ���³���λ��
	//	setSceneScrollPosition(hero->getPosition());
}
