#include "MyGameLayer.h"

MyGameLayer::MyGameLayer(void)
{
	MysGlobal->MygameLayer = this;
}

MyGameLayer::~MyGameLayer(void)
{
	this->unscheduleAllSelectors();
}

bool MyGameLayer::init()
{
	//解析tmx地图
	char temp[20];
	sprintf(temp, "%d.tmx", MysGlobal->currentLevel);

	map = MyGameMap::gameMapWithTMXFile(temp);

	addChild(map, 1, 1);

	//调用Hero类的静态方法创建实例
	myhero = MyHero::create();
	//设置Hero的起始位置
	myhero->setPosition(map->positionForTileCoord(MysGlobal->heroSpawnTileCoord));
	addChild(myhero, kZHero, kZHero);

	

	schedule(schedule_selector(MyGameLayer::update));

	return true;
}
void MyGameLayer::update(float time)
{
	//如果勇士不在行走状态，不需要更新场景位置
	if (myhero->isHeroMoving)
	{
		setSceneScrollPosition(myhero->getPosition());
	}
}
//传入勇士当前位置信息，将场景移动到相应位置
void MyGameLayer::setSceneScrollPosition(Point position)
{
	//获取屏幕尺寸
	Size screenSize = Director::getInstance()->getWinSize();

	//计算Tilemap的宽高，单位是像素
	Size mapSizeInPixel = CCSizeMake(map->getMapSize().width * map->getTileSize().width, map->getMapSize().height * map->getTileSize().height);

	//取勇士当前x坐标和屏幕中点x的最大值，如果勇士的x值较大，则会滚动
	float x = MAX(position.x, screenSize.width / 2.0f);
	float y = MAX(position.y, screenSize.height / 2.0f);

	//地图总宽度大于屏幕宽度的时候才有可能滚动
	if (mapSizeInPixel.width  > screenSize.width)
	{
		//场景滚动的最大距离不能超过地图总宽减去屏幕宽的1/2
		x = MIN(x, mapSizeInPixel.width - screenSize.width / 2.0f);
	}

	if (mapSizeInPixel.height > screenSize.height)
	{
		y = MIN(y, mapSizeInPixel.height - screenSize.height / 2.0f);
	}

	//勇士的实际位置
	Point heroPosition = Point(x, y);

	//屏幕中点位置
	Point screenCenter = Point(screenSize.width/2.0f, screenSize.height/2.0f);

	//计算勇士实际位置和重点位置的距离
	Point scrollPosition = screenCenter - heroPosition;

	//将场景移动到相应位置
	this->setPosition(scrollPosition);

	CCLog("%f,%f", scrollPosition.x, scrollPosition.y);
}
