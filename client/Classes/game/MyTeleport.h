#ifndef __TELEPORT_H__
#define __TELEPORT_H__

#include "MHGame.h"

USING_NS_CC;

class MyTeleport : public Ref
{
public:
	MyTeleport(const ValueMap &dict, int x, int y);

	~MyTeleport(void);

	//���͵�����λ��
	Point tileCoord;

	//���͵�Ŀ������ʿ��������
	Point heroTileCoord;

	//Ŀ���ͼ�Ĳ���
	int targetMap;

	//Ψһ��ID
	int index;

	//ͼƬ������ļ�·��
	std::string imagePath;

	Sprite *teleportSprite;
};
#endif