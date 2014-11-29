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
class MenuLayer4 : public Layer
{
public:
    MenuLayer4(void);
    ~MenuLayer4();

public:
    void menuCallback(Ref* sender);
    void backCallback(Ref* sender);

    //CREATE_NODE(MenuLayer4);
};
class MenuLayerMainMenu : public Layer
{
protected:
    MenuItem*    _disabledItem;
    EventListenerTouchOneByOne* _touchListener;

public:
    MenuLayerMainMenu(void);
    ~MenuLayerMainMenu();

public:
    bool onTouchBegan(Touch *touch, Event * event);
    void onTouchEnded(Touch *touch, Event * event);
    void onTouchCancelled(Touch *touch, Event * event);
    void onTouchMoved(Touch *touch, Event * event);

    void allowTouches(float dt);
    void menuCallback(Ref* sender);
    void menuCallbackConfig(Ref* sender);
    void menuCallbackDisabled(Ref* sender);
    void menuCallback2(Ref* sender);
    void menuCallbackPriorityTest(Ref* sender);
    void menuCallbackBugsTest(Ref *pSender);
    void onQuit(Ref* sender);
    void menuMovingCallback(Ref *pSender);

    //CREATE_NODE(MenuLayer1);
};
#endif // __HELLOWORLD_SCENE_H__
