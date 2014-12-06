#ifndef __MY_GAME_MAP_H__
#define __MY_GAME_MAP_H__

#include "MHGame.h"

USING_NS_CC;


//�̳���CCTMXTIledMap
class MyGameMap : public TMXTiledMap
{
	//ֻ����������ȡ��ͼ��CC_PROPERTY_READONLY

public:
	MyGameMap(void);
	~MyGameMap(void);

	//��̬��������������GameMapʵ��
	static MyGameMap* gameMapWithTMXFile(const char *tmxFile);

	//TiledMap��cocos2d-x����ϵ�໥ת���ķ���
	Point tileCoordForPosition(Point position);
	Point positionForTileCoord(Point tileCoord);
	void showEnemyHitEffect(Point tileCoord);
	protected:
	//TiledMap����ĳ�ʼ������
	void extraInit();

	//��ʼ������
	void initObject();

	//������ͼ����������
	void enableAnitiAliasForEachLayer();

};

#endif