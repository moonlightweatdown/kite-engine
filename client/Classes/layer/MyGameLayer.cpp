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
	//解析tmx地图
	char temp[20];
	sprintf(temp, "%d.tmx", MysGlobal->currentLevel);

	map = MyGameMap::gameMapWithTMXFile("m.tmx");

	addChild(map, 1, 1);

	//调用Hero类的静态方法创建实例
	myhero = MyHero::create();
	//设置Hero的起始位置
	myhero->setPosition(map->positionForTileCoord(MysGlobal->heroSpawnTileCoord));
	addChild(myhero, kZHero, kZHero);

	schedule(schedule_selector(MyGameLayer::update));

	return true;
}
void MyGameLayer::update(float time)
{
	//如果勇士不在行走状态，不需要更新场景位置
	//	setSceneScrollPosition(hero->getPosition());
}
