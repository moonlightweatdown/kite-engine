#ifndef __CONTROLLAYER_H__
#define __CONTROLLAYER_H__

#include "MTGame.h"

USING_NS_CC;

class ControlLayer : public Layer
{
public:
	ControlLayer(void);
	~ControlLayer(void);

	//node��������ô˺���
	virtual bool init();

	CREATE_FUNC(ControlLayer);

	//����ť����¼��Ļص�
	void menuCallBackMove(cocos2d::Ref* pSender);

	//�رհ�ť����¼��Ļص�
	void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif
