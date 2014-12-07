#ifndef __MY_HERO_H__
#define __MY_HERO_H__

#include "MHGame.h"

USING_NS_CC;


//��ʿ��̳���CCNode
class MyHero : public Node
{
public:
	MyHero(void);
	~MyHero(void);

	//��ʼ������
	bool init();

	CREATE_FUNC(MyHero);
		//����ʿ��ָ�������ƶ�һ��
	void move(HeroDirection direction);

	//������ʿ����
	void setFaceDirection(HeroDirection direction);

	//��ʼս���߼�
	void fight();

	//����
	void doTeleport(MyTeleport *teleport);

	//��ʶ��ʿ�Ƿ����ƶ�״̬
	bool isHeroMoving;

	//��ʶ��ʿ�Ƿ���ս��״̬
	bool isHeroFighting;

	//��ʶ��ʿ�Ƿ��ڿ���״̬
	bool isDoorOpening;
	protected:
	//������ʾ��ʿ����ľ���
	Sprite *heroSprite;
	
	//��ʱ����Ŀ���Tilemap����
	Point targetTileCoord;
	
	//��ʱ����Ŀ���cocos2d-x����
	Point targetPosition;
	
	//��ʱ��������ʼ��ͼ��ID
	int targetDoorGID;
	
	//��ʾս�������ľ���
	Sprite *fightSprite;

	//��ײ��ⷽ��
	CollisionType checkCollision(Point heroPosition);

	//�ƶ���ɺ�Ļص�����
	void onMoveDone(Node* pTarget, void* data);

	
};

#endif