#include "MyTeleport.h"
MyTeleport::MyTeleport(const ValueMap &dict, int x, int y)
{
	Point position = Point(x, y);

	//取得目标地图的层数
	key = "targetMap";
	targetMap = dict.at(key).asInt();

	//获取image项
	key = "image";
	imagePath = dict.at(key).asString();

	//创建用于显示Teleport的精灵
	teleportSprite = Sprite::create(imagePath);
	teleportSprite->setAnchorPoint(Point::ZERO);
	teleportSprite->setPosition(position)
	gameLayer->addChild(teleportSprite, kZTeleport);
}

MyTeleport::~MyTeleport(void)
{
}