#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:
    virtual bool init();  
    static cocos2d::Scene* createScene();
    CREATE_FUNC(HelloWorld);
};
class MainLayer : public Layer
{
public:
    MainLayer();
    void menuCloseCallback(Ref* pSender);
    bool onTouchBegan(Touch* touch, Event  *event);
    void onTouchEnded(Touch* touch, Event  *event);
};

#endif // __HELLOWORLD_SCENE_H__
