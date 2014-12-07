#ifndef __MY_HERO_H__
#define __MY_HERO_H__

#include "MHGame.h"

USING_NS_CC;


//勇士类继承自CCNode
class MyHero : public Node
{
public:
	MyHero(void);
	~MyHero(void);

	//初始化方法
	bool init();

	CREATE_FUNC(MyHero);
		//让勇士向指定方向移动一格
	void move(HeroDirection direction);

	//设置勇士朝向
	void setFaceDirection(HeroDirection direction);

	//开始战斗逻辑
	void fight();

	//传送
	void doTeleport(MyTeleport *teleport);

	//标识勇士是否在移动状态
	bool isHeroMoving;

	//标识勇士是否在战斗状态
	bool isHeroFighting;

	//标识勇士是否在开门状态
	bool isDoorOpening;
	protected:
	//用于显示勇士形象的精灵
	Sprite *heroSprite;
	
	//临时保存目标的Tilemap坐标
	Point targetTileCoord;
	
	//临时保存目标的cocos2d-x坐标
	Point targetPosition;
	
	//临时保存门起始的图块ID
	int targetDoorGID;
	
	//显示战斗动画的精灵
	Sprite *fightSprite;

	//碰撞检测方法
	CollisionType checkCollision(Point heroPosition);

	//移动完成后的回调函数
	void onMoveDone(Node* pTarget, void* data);

	
};

#endif