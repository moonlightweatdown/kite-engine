#ifndef __MY_TELEPORT_H__
#define __MY_TELEPORT_H__

#include "MHGame.h"

USING_NS_CC;

class MyTeleport : public Ref
{
public:
	MyTeleport(const ValueMap &dict, int x, int y);

	~MyTeleport(void);

	//传送点所在位置
	Point tileCoord;

	//传送到目标层后，勇士所在坐标
	Point heroTileCoord;

	//目标地图的层数
	int targetMap;

	//唯一的ID
	int index;

	//图片纹理的文件路径
	std::string imagePath;

	Sprite *teleportSprite;
};
#endif