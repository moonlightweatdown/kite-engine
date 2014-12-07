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
	//����tmx��ͼ
	char temp[20];
	sprintf(temp, "%d.tmx", MysGlobal->currentLevel);

	map = MyGameMap::gameMapWithTMXFile(temp);

	addChild(map, 1, 1);

	//����Hero��ľ�̬��������ʵ��
	myhero = MyHero::create();
	//����Hero����ʼλ��
	myhero->setPosition(map->positionForTileCoord(MysGlobal->heroSpawnTileCoord));
	addChild(myhero, kZHero, kZHero);

	

	schedule(schedule_selector(MyGameLayer::update));

	return true;
}
void MyGameLayer::update(float time)
{
	//�����ʿ��������״̬������Ҫ���³���λ��
	if (myhero->isHeroMoving)
	{
		setSceneScrollPosition(myhero->getPosition());
	}
}
//������ʿ��ǰλ����Ϣ���������ƶ�����Ӧλ��
void MyGameLayer::setSceneScrollPosition(Point position)
{
	//��ȡ��Ļ�ߴ�
	Size screenSize = Director::getInstance()->getWinSize();

	//����Tilemap�Ŀ�ߣ���λ������
	Size mapSizeInPixel = CCSizeMake(map->getMapSize().width * map->getTileSize().width, map->getMapSize().height * map->getTileSize().height);

	//ȡ��ʿ��ǰx�������Ļ�е�x�����ֵ�������ʿ��xֵ�ϴ�������
	float x = MAX(position.x, screenSize.width / 2.0f);
	float y = MAX(position.y, screenSize.height / 2.0f);

	//��ͼ�ܿ�ȴ�����Ļ��ȵ�ʱ����п��ܹ���
	if (mapSizeInPixel.width  > screenSize.width)
	{
		//���������������벻�ܳ�����ͼ�ܿ��ȥ��Ļ���1/2
		x = MIN(x, mapSizeInPixel.width - screenSize.width / 2.0f);
	}

	if (mapSizeInPixel.height > screenSize.height)
	{
		y = MIN(y, mapSizeInPixel.height - screenSize.height / 2.0f);
	}

	//��ʿ��ʵ��λ��
	Point heroPosition = Point(x, y);

	//��Ļ�е�λ��
	Point screenCenter = Point(screenSize.width/2.0f, screenSize.height/2.0f);

	//������ʿʵ��λ�ú��ص�λ�õľ���
	Point scrollPosition = screenCenter - heroPosition;

	//�������ƶ�����Ӧλ��
	this->setPosition(scrollPosition);

	CCLog("%f,%f", scrollPosition.x, scrollPosition.y);
}
