#ifndef _MY_GLOBAL_H_
#define _MY_GLOBAL_H_

#include "MHGame.h"
using namespace cocos2d;

class MyGameScene;
class MyGameLayer;
class MyGameMap;
class MyHero;
class MyAnimationManager;
class MyControlLayer;
class MyGlobal : public Singleton<MyGlobal>
{
public:
	MyGlobal(void);
	~MyGlobal(void);

	MyGameScene *MygameScene;

	//游戏主图层
	MyGameLayer *MygameLayer;
	
	//勇士
	MyHero *Myhero;
	MyAnimationManager *MyAnima;

	MyControlLayer *MycontrolLayer;
	//游戏地图
	MyGameMap *MygameMap;



	//目标地图的层数
	int currentLevel;

	//勇士出现的起始位置
	Point heroSpawnTileCoord;
};

#define MysGlobal MyGlobal::instance()

#endif