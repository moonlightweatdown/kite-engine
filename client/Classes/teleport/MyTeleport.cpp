#include "MyTeleport.h"

MyTeleport::MyTeleport(const ValueMap &dict, int x, int y)
{
	Point position = Point(x, y);

	//���͵����ڵ�TileMapλ��
	tileCoord = MysGlobal->MygameMap->tileCoordForPosition(Point(x, y));

	//�ó���ʿ��Ŀ������ʼλ��
	std::string key = "heroTileCoordX";
	int x1 = dict.at(key).asInt();

	key = "heroTileCoordY";
	int y1 = dict.at(key).asInt();

	heroTileCoord = Point(x1, y1);

	//ȡ��Ŀ���ͼ�Ĳ���
	key = "targetMap";
	targetMap = dict.at(key).asInt();

	//��ȡimage��
	key = "image";
	imagePath = dict.at(key).asString();

	//����������ʾTeleport�ľ���
	teleportSprite = Sprite::create(imagePath);
	teleportSprite->setAnchorPoint(Point::ZERO);
	teleportSprite->setPosition(position);
	MysGlobal->MygameLayer->addChild(teleportSprite, kZTeleport);
}

MyTeleport::~MyTeleport(void)
{
}