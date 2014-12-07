#ifndef __MY_CONTROLLAYER_H__
#define __MY_CONTROLLAYER_H__

#include "MHGame.h"

USING_NS_CC;

class MyControlLayer : public Layer
{
public:
	MyControlLayer(void);
	~MyControlLayer(void);

	//node方法会调用此函数
	virtual bool init();

	CREATE_FUNC(MyControlLayer);

	//方向按钮点击事件的回调
	void menuCallBackMove(cocos2d::Ref* pSender);

	//关闭按钮点击事件的回调
	void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif
