#ifndef __MY_CONTROLLAYER_H__
#define __MY_CONTROLLAYER_H__

#include "MHGame.h"

USING_NS_CC;

class MyControlLayer : public Layer
{
public:
	MyControlLayer(void);
	~MyControlLayer(void);

	//node��������ô˺���
	virtual bool init();

	CREATE_FUNC(MyControlLayer);

	//����ť����¼��Ļص�
	void menuCallBackMove(cocos2d::Ref* pSender);

	//�رհ�ť����¼��Ļص�
	void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif
