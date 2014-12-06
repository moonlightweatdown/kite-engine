#ifndef __MY_GAME_LAYER_H__
#define __MY_GAME_LAYER_H__

#include "cocos2d.h"
#include "MHGame.h"
using namespace cocos2d;

class MyGameMap;
class MyHero;
class MyGameLayer : public Layer
{
public:
	MyGameLayer(void);
	~MyGameLayer(void);

	virtual bool init();

	CREATE_FUNC(MyGameLayer);

	void update(float time);
	void setSceneScrollPosition(Point position);

	//显示tip
	void showTip(const char *tip, Point position);

protected:
	MyGameMap *map;
	MyHero *myhero;

	void onShowTipDone(Node* pSender);
		//开启各图层的纹理抗锯齿

};

#endif