#ifndef __MY_GAME_MAP_H__
#define __MY_GAME_MAP_H__

#include "MHGame.h"

USING_NS_CC;

class MyTeleport;
//继承自CCTMXTIledMap
class MyGameMap : public TMXTiledMap
{
	//只读变量，获取各图层CC_PROPERTY_READONLY
	CC_SYNTHESIZE(TMXLayer*, noLayer, NoLayer);
	CC_SYNTHESIZE(TMXLayer*, canLayer, CanLayer);

public:
	MyGameMap(void);
	~MyGameMap(void);

	//静态方法，用于生成GameMap实例
	static MyGameMap* gameMapWithTMXFile(const char *tmxFile);

	//TiledMap和cocos2d-x坐标系相互转换的方法
	Point tileCoordForPosition(Point position);
	Point positionForTileCoord(Point tileCoord);
	void showEnemyHitEffect(Point tileCoord);
	Map<int, MyTeleport*> myteleportDict;
	protected:
	//TiledMap额外的初始化方法
	void extraInit();

	//初始化对象
	void initObject();

	//开启各图层的纹理抗锯齿
	void enableAnitiAliasForEachLayer();

};

#endif