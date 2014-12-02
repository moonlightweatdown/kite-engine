#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "MTGame.h"

using namespace cocos2d;

class GameMap;
class Hero;

class GameLayer : public Layer
{
public:
	GameLayer(void);
	~GameLayer(void);

	virtual bool init();

	CREATE_FUNC(GameLayer);

	void update(float time);
	void setSceneScrollPosition(Point position);

	//œ‘ ætip
	void showTip(const char *tip, Point position);

protected:
	GameMap *map;
	Hero *hero;
	void onShowTipDone(Node* pSender);
};

#endif