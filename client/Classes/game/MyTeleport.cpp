#include "MyTeleport.h"
MyTeleport::MyTeleport(const ValueMap &dict, int x, int y)
{
	Point position = Point(x, y);

	//ȡ��Ŀ���ͼ�Ĳ���
	key = "targetMap";
	targetMap = dict.at(key).asInt();

	//��ȡimage��
	key = "image";
	imagePath = dict.at(key).asString();

	//����������ʾTeleport�ľ���
	teleportSprite = Sprite::create(imagePath);
	teleportSprite->setAnchorPoint(Point::ZERO);
	teleportSprite->setPosition(position)
	gameLayer->addChild(teleportSprite, kZTeleport);
}

MyTeleport::~MyTeleport(void)
{
}