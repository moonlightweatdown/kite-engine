#include "GameLayer.h"

GameLayer::GameLayer(void)
{
	sGlobal->gameLayer = this;
}

GameLayer::~GameLayer(void)
{
	this->unscheduleAllSelectors();
}

bool GameLayer::init()
{
	//����tmx��ͼ
	char temp[20];
	sprintf(temp, "%d.tmx", sGlobal->currentLevel);

	map = GameMap::gameMapWithTMXFile(temp);

	addChild(map, kZMap, kZMap);

	//����Hero��ľ�̬��������ʵ��
	hero = Hero::create();

	//����Hero����ʼλ��
	hero->setPosition(map->positionForTileCoord(sGlobal->heroSpawnTileCoord));

	//��Hero����GameLayer
	addChild(hero, kZHero, kZHero);

	schedule(schedule_selector(GameLayer::update));

	return true;
}

void GameLayer::update(float time)
{
	//�����ʿ��������״̬������Ҫ���³���λ��
	if (hero->isHeroMoving)
	{
		setSceneScrollPosition(hero->getPosition());
	}
}

//������ʿ��ǰλ����Ϣ���������ƶ�����Ӧλ��
void GameLayer::setSceneScrollPosition(Point position)
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

//��ʾ��ʾ��Ϣ
void GameLayer::showTip(const char *tip, Point startPosition)
{
	//�½�һ���ı���ǩ
	LabelTTF *tipLabel = LabelTTF::create(tip, "Arial", 20);

	tipLabel->setPosition(startPosition + Point(16, 16));

	this->addChild(tipLabel, kZTip,kZTip);

	//���嶯��Ч��
	Action* action = Sequence::create(
		MoveBy::create(0.5f, Point(0, 32)), 
		DelayTime::create(0.5f), FadeOut::create(0.2f), 
		CallFuncN::create(CC_CALLBACK_1(GameLayer::onShowTipDone, this)),
		NULL);

	tipLabel->runAction(action);
}

//��ʾ��Ϣ��ʾ���Ļص�
void GameLayer::onShowTipDone(Node* pSender)
{
	//ɾ���ı���ǩ
	this->getChildByTag(kZTip)->removeFromParentAndCleanup(true);
}