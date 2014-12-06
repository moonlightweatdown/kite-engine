#include "MyGameMap.h"

MyGameMap::MyGameMap(void)
{
	MysGlobal->MygameMap = this;
}

MyGameMap::~MyGameMap(void)
{
	this->unscheduleAllSelectors();
}

//��̬��������������GameMapʵ��
MyGameMap* MyGameMap::gameMapWithTMXFile(const char *tmxFile)
{
	//newһ������
	MyGameMap *pRet = new MyGameMap();

	//����init����
	if (pRet->initWithTMXFile(tmxFile))
	{

		//��ʵ������autorelease�أ�ͳһ��������ƶ������������
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

//��cocos2d-x����ת��ΪTilemap����
Point MyGameMap::tileCoordForPosition(Point position)
{
	int x = position.x / this->getTileSize().width;
	int y = (((this->getMapSize().height - 1) * this->getTileSize().height) - position.y) / this->getTileSize().height;
	return Point(x, y);
}

//��Tilemap����ת��Ϊcocos2d-x����
Point MyGameMap::positionForTileCoord(Point tileCoord)
{
	Point pos = Point((tileCoord.x * this->getTileSize().width), ((this->getMapSize().height - tileCoord.y - 1) * this->getTileSize().height));
	return pos;
}

