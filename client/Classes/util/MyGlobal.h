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

	//��Ϸ��ͼ��
	MyGameLayer *MygameLayer;
	
	//��ʿ
	MyHero *Myhero;
	MyAnimationManager *MyAnima;

	MyControlLayer *MycontrolLayer;
	//��Ϸ��ͼ
	MyGameMap *MygameMap;



	//Ŀ���ͼ�Ĳ���
	int currentLevel;

	//��ʿ���ֵ���ʼλ��
	Point heroSpawnTileCoord;
};

#define MysGlobal MyGlobal::instance()

#endif