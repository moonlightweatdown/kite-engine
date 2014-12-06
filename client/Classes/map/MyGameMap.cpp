#include "MyGameMap.h"

MyGameMap::MyGameMap(void)
{
	MysGlobal->MygameMap = this;
}

MyGameMap::~MyGameMap(void)
{
	this->unscheduleAllSelectors();
}

//静态方法，用于生成GameMap实例
MyGameMap* MyGameMap::gameMapWithTMXFile(const char *tmxFile)
{
	//new一个对象
	MyGameMap *pRet = new MyGameMap();

	//调用init方法
	if (pRet->initWithTMXFile(tmxFile))
	{

		//将实例放入autorelease池，统一由引擎控制对象的生命周期
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

//从cocos2d-x坐标转换为Tilemap坐标
Point MyGameMap::tileCoordForPosition(Point position)
{
	int x = position.x / this->getTileSize().width;
	int y = (((this->getMapSize().height - 1) * this->getTileSize().height) - position.y) / this->getTileSize().height;
	return Point(x, y);
}

//从Tilemap坐标转换为cocos2d-x坐标
Point MyGameMap::positionForTileCoord(Point tileCoord)
{
	Point pos = Point((tileCoord.x * this->getTileSize().width), ((this->getMapSize().height - tileCoord.y - 1) * this->getTileSize().height));
	return pos;
}

