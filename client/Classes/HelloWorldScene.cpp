#include "HelloWorldScene.h"
#include "testResource.h"
USING_NS_CC;
enum
{
    kTagSprite = 1,
};
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
   // auto layer = HelloWorld::create();
	auto layer = new MainLayer();
	auto layer1 = new MenuLayerMainMenu();
	auto layer4 = new MenuLayer4();
    layer->autorelease();
   //  layer1->release();
	// layer4->autorelease();
  // layer4->autorelease();
    auto layers = LayerMultiplex::create(layer1,layer4,NULL);
    //addChild(layers, 0); 
  //  addChild(layer);
   // Director::getInstance()->replaceScene(this);
    // add layer as a child to scene
    scene->addChild(layers);
	scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    } 
    
 
    return true;
}
MainLayer::MainLayer()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainLayer::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MainLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(MainLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto sprite = Sprite::create(s_pathGrossini);
    
    auto layer = LayerColor::create(Color4B(255,255,0,255));
  //  addChild(layer, -1);
        
    addChild(sprite, 0, kTagSprite);
    sprite->setPosition( Vec2(20,150) );
    
    sprite->runAction( JumpTo::create(4, Vec2(300,48), 100, 4) );
    
    layer->runAction( RepeatForever::create(
                                Sequence::create(
                                        FadeIn::create(1),
                                        FadeOut::create(1),
                                        NULL)
                      )); 
}
bool MainLayer::onTouchBegan(Touch* touch, Event  *event)
{
    return true;
}

void MainLayer::onTouchEnded(Touch* touch, Event  *event)
{
    auto location = touch->getLocation();

    auto s = getChildByTag(kTagSprite);
    s->stopAllActions();
    s->runAction( MoveTo::create(1, Vec2(location.x, location.y) ) );
    float o = location.x - s->getPosition().x;
    float a = location.y - s->getPosition().y;
    float at = (float) CC_RADIANS_TO_DEGREES( atanf( o/a) );
    
    if( a < 0 ) 
    {
        if(  o < 0 )
            at = 180 + fabs(at);
        else
            at = 180 - fabs(at);    
    }
    
    s->runAction( RotateTo::create(1, at) );
}

void MainLayer::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//------------------------------------------------------------------
//
// MenuLayer4
//
//------------------------------------------------------------------
MenuLayer4::MenuLayer4()
{
    MenuItemFont::setFontName("American Typewriter");
    MenuItemFont::setFontSize(18);
	auto title1 = MenuItemFont::create("Sound");
    title1->setEnabled(false);
	MenuItemFont::setFontName( "fonts/Marker Felt.ttf" );
    MenuItemFont::setFontSize(18);
    auto item1 = MenuItemToggle::createWithCallback( CC_CALLBACK_1(MenuLayer4::menuCallback, this),
                                                                MenuItemFont::create( "On" ),
                                                                MenuItemFont::create( "Off"),
                                                                NULL );
    MenuItemFont::setFontName( "American Typewriter" );
    MenuItemFont::setFontSize(18);
    auto title2 = MenuItemFont::create( "Music" );
    title2->setEnabled(false);
    MenuItemFont::setFontName( "fonts/Marker Felt.ttf" );
    MenuItemFont::setFontSize(18);
    auto item2 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuLayer4::menuCallback, this),
                                                                MenuItemFont::create( "On" ),
                                                                MenuItemFont::create( "Off"),
                                                                NULL );
	    
    MenuItemFont::setFontName( "American Typewriter" );
    MenuItemFont::setFontSize(18);
    auto title3 = MenuItemFont::create( "Quality" );
    title3->setEnabled( false );
    MenuItemFont::setFontName( "fonts/Marker Felt.ttf" );
    MenuItemFont::setFontSize(18);
    auto item3 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuLayer4::menuCallback, this),
                                                                MenuItemFont::create( "High" ),
                                                                MenuItemFont::create( "Low" ),
                                                                NULL );
   MenuItemFont::setFontName( "American Typewriter" );
    MenuItemFont::setFontSize(18);
    auto title4 = MenuItemFont::create( "Orientation" );
    title4->setEnabled(false);
    MenuItemFont::setFontName( "fonts/Marker Felt.ttf" );
    MenuItemFont::setFontSize(18);
    auto item4 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuLayer4::menuCallback, this),
                                                                MenuItemFont::create( "Off" ), 
                                                                NULL );

    MenuItemFont::setFontName( "American Typewriter" );
    MenuItemFont::setFontSize(18);
    auto title5 = MenuItemFont::create( "other" );
    title5->setEnabled(false);
    MenuItemFont::setFontName( "fonts/Marker Felt.ttf" );
    MenuItemFont::setFontSize(18);
    auto back = MenuItemFont::create("go back", CC_CALLBACK_1(MenuLayer4::backCallback, this) );
    auto menu = Menu::create(
                  title1,
                  title2,
				  title3,
                  title4,
				  title5,
                   NULL ); // 9 items.
    auto menu2 = Menu::create(
                  item1,
                  item2,
				  item3,
                  item4,
				  back,
                   NULL ); // 9 items.
    // menu->alignItemsInColumns(2, 2, 2, 2, NULL);
    menu->alignItemsVerticallyWithPadding( 30 );
     menu2->alignItemsVerticallyWithPadding( 30 );
    addChild( menu );
	addChild( menu2 );
    auto s = Director::getInstance()->getWinSize();
    menu->setPosition(Vec2(s.width/1.4, s.height/1.6));
	menu->setScale(1);
    menu2->setPosition(Vec2(s.width/1.2, s.height/1.6));
	menu2->setScale(1);
}

MenuLayer4::~MenuLayer4()
{
}

void MenuLayer4::menuCallback(Ref* sender)
{
    //CCLOG("selected item: %x index:%d", dynamic_cast<MenuItemToggle*>(sender)->selectedItem(), dynamic_cast<MenuItemToggle*>(sender)->selectedIndex() ); 
}

void MenuLayer4::backCallback(Ref* sender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(0);
}
//------------------------------------------------------------------
//
// MenuLayerMainMenu
//
//------------------------------------------------------------------
MenuLayerMainMenu::MenuLayerMainMenu()
{
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(true);
    _touchListener->onTouchBegan = CC_CALLBACK_2(MenuLayerMainMenu::onTouchBegan, this);
    _touchListener->onTouchMoved = CC_CALLBACK_2(MenuLayerMainMenu::onTouchMoved, this);
    _touchListener->onTouchEnded = CC_CALLBACK_2(MenuLayerMainMenu::onTouchEnded, this);
    _touchListener->onTouchCancelled = CC_CALLBACK_2(MenuLayerMainMenu::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithFixedPriority(_touchListener, 1);

    
    // Font Item
    auto item4 = MenuItemFont::create("I toggle enable items", [&](Ref *sender) {
		_disabledItem->setEnabled(! _disabledItem->isEnabled() );
	});

    item4->setFontSizeObj(20);
    item4->setFontName("fonts/Marker Felt.ttf");
    
    // Label Item (LabelBMFont)
     MenuItemFont::setFontName("fonts/Marker Felt.ttf");;
    auto item5 = MenuItemFont::create("setting", CC_CALLBACK_1(MenuLayerMainMenu::menuCallbackConfig, this));

    // Events
    MenuItemFont::setFontName("fonts/Marker Felt.ttf");
    // Bugs Item
    auto item6 = MenuItemFont::create("Bugs", CC_CALLBACK_1(MenuLayerMainMenu::menuCallbackBugsTest, this));

    // Font Item
    auto item7= MenuItemFont::create("Quit", CC_CALLBACK_1(MenuLayerMainMenu::onQuit, this));
    
    auto item8 = MenuItemFont::create("Remove menu item when moving", CC_CALLBACK_1(MenuLayerMainMenu::menuMovingCallback, this));
    
    auto color_action = TintBy::create(0.5f, 0, -255, -255);
    auto color_back = color_action->reverse();
    auto seq = Sequence::create(color_action, color_back, NULL);
    item7->runAction(RepeatForever::create(seq));

    auto menu = Menu::create(item4, item5, item6, item7, item8,  NULL);
    menu->alignItemsVertically();
    
    
    // elastic effect
    auto s = Director::getInstance()->getWinSize();
    menu->alignItemsVerticallyWithPadding( 30 );
    addChild( menu );
    menu->setPosition(Vec2(s.width/2, s.height/2));
	menu->setScale(1);
}

bool MenuLayerMainMenu::onTouchBegan(Touch *touch, Event * event)
{
    return true;
}

void MenuLayerMainMenu::onTouchEnded(Touch *touch, Event * event)
{
}

void MenuLayerMainMenu::onTouchCancelled(Touch *touch, Event * event)
{
}

void MenuLayerMainMenu::onTouchMoved(Touch *touch, Event * event)
{
}

MenuLayerMainMenu::~MenuLayerMainMenu()
{
    _eventDispatcher->removeEventListener(_touchListener);
    _disabledItem->release();
}

void MenuLayerMainMenu::menuCallback(Ref* sender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(1);
}

void MenuLayerMainMenu::menuCallbackConfig(Ref* sender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(1);
}

void MenuLayerMainMenu::allowTouches(float dt)
{
    _eventDispatcher->setPriority(_touchListener, 1);
    unscheduleAllSelectors();
    log("TOUCHES ALLOWED AGAIN");
}

void MenuLayerMainMenu::menuCallbackDisabled(Ref* sender) 
{
    // hijack all touch events for 5 seconds
    _eventDispatcher->setPriority(_touchListener, -1);
    schedule(schedule_selector(MenuLayerMainMenu::allowTouches), 5.0f);
    log("TOUCHES DISABLED FOR 5 SECONDS");
}

void MenuLayerMainMenu::menuCallback2(Ref* sender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(2);
}

void MenuLayerMainMenu::menuCallbackBugsTest(Ref *pSender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(4);
}

void MenuLayerMainMenu::onQuit(Ref* sender)
{
    //[[Director sharedDirector] end];
    //getCocosApp()->exit();
}

void MenuLayerMainMenu::menuMovingCallback(Ref *pSender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(5);
}