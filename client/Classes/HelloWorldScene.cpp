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
	auto layer4 = new MenuLayer4();
   layer->autorelease();
  // layer4->autorelease();

  //  addChild(layer);
   // Director::getInstance()->replaceScene(this);
    // add layer as a child to scene
    scene->addChild(layer);
	scene->addChild(layer4);


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
    auto menu = Menu::create(
                  title1,
                  title2,
				  title3,
                  title4,
                   NULL ); // 9 items.
    auto menu2 = Menu::create(
                  item1,
                  item2,
				  item3,
                  item4,
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