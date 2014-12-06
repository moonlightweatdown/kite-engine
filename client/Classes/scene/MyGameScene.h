#ifndef __MY__GAME_SCENE_H__
#define __MY__GAME_SCENE_H__

//包含公用头文件
#include "MHGame.h"

//使用cocos2d命名空间
using namespace cocos2d;

//GameScene继承CCScene
class MyGameScene : public Scene
{
public:
	MyGameScene(void);
	~MyGameScene(void);

	//初始化函数
	virtual bool init();

	CREATE_FUNC(MyGameScene);

	void switchMap();
	void resetGameLayer();
	void removeFadeLayer();
};

#endif