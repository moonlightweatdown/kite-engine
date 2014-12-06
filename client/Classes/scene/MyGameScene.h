#ifndef __MY__GAME_SCENE_H__
#define __MY__GAME_SCENE_H__

//��������ͷ�ļ�
#include "MHGame.h"

//ʹ��cocos2d�����ռ�
using namespace cocos2d;

//GameScene�̳�CCScene
class MyGameScene : public Scene
{
public:
	MyGameScene(void);
	~MyGameScene(void);

	//��ʼ������
	virtual bool init();

	CREATE_FUNC(MyGameScene);

	void switchMap();
	void resetGameLayer();
	void removeFadeLayer();
};

#endif