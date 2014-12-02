#include "Hero.h"

Hero::Hero()
{
	sGlobal->hero = this;
}

Hero::~Hero()
{

}

bool Hero::init()
{
	if (!Node::init())
	{
		return false;
	}

	//�����������߶����ĵ�һ֡��������spriteWithSpriteFrame
	heroSprite = Sprite::createWithSpriteFrame(sAnimationMgr->getAnimation(kDown)->getFrames().at(0)->getSpriteFrame());

	//����ê��
	heroSprite->setAnchorPoint(Point::ZERO);

	//��������ʾ��heroSprite�ӵ��Լ��Ľڵ���
	this->addChild(heroSprite);

	//�����յ�ս����������
	fightSprite = Sprite::create();

	this->addChild(fightSprite);

	//һ��ʼ������move״̬��
	isHeroMoving = false;
	isHeroFighting = false;
	isDoorOpening = false;
	return true;
}

void Hero::move(HeroDirection direction) 
{
	if (isHeroMoving)
	{
		return;
	}

	//�ƶ��ľ���
	Point moveByPosition;

	//���ݷ�������ƶ��ľ���
	switch (direction)
	{
	case kDown:
		moveByPosition = Point(0, -32);
		break;
	case kLeft:
		moveByPosition = Point(-32, 0);
		break;
	case kRight:
		moveByPosition = Point(32, 0);
		break;
	case kUp:
		moveByPosition = Point(0, 32);
		break;
	}

	//����Ŀ�����꣬�õ�ǰ��ʿ��������ƶ�����
	targetPosition = this->getPosition() + moveByPosition;

	//����checkCollision�����ײ���ͣ������ǽ�ڡ�����ţ���ֻ��Ҫ������ʿ�ĳ���
	CollisionType collisionType = checkCollision(targetPosition);

	if (collisionType == kWall 
		|| collisionType == kEnemy
		|| collisionType == kDoor 
		|| collisionType == kNPC)
	{
		setFaceDirection((HeroDirection)direction);
		return;
	}

	//heroSprite���������߶���
	heroSprite->runAction(sAnimationMgr->createAnimate(direction));

	//�������λ�ƣ�����ʱ����onMoveDone���� �ѷ�����Ϣ���ݸ�onMoveDone����
	Action *action = Sequence::create(
		MoveBy::create(0.20f, moveByPosition), 
		CallFuncN::create(CC_CALLBACK_1(Hero::onMoveDone, this, (void*)direction)), 
		NULL);

	this->runAction(action);

	isHeroMoving = true;
}

void Hero::onMoveDone(Node* pTarget, void* data)
{
	//��void*��ת��Ϊint���ٴ�intת����ö������
	int direction = (int) data;
	setFaceDirection((HeroDirection)direction);
	isHeroMoving = false;
	sGlobal->gameLayer->setSceneScrollPosition(this->getPosition());
}

void Hero::setFaceDirection(HeroDirection direction)
{
	heroSprite->setTextureRect(Rect(0, 32*direction, 32, 32));
}

//�ж���ײ����
CollisionType Hero::checkCollision(Point heroPosition) 
{
	//cocos2d-x����ת��ΪTilemap����
	targetTileCoord = sGlobal->gameMap->tileCoordForPosition(heroPosition);

	//�����ʿ���곬����ͼ�߽磬����kWall���ͣ���ֹ���ƶ�
	if (heroPosition.x < 0
		|| targetTileCoord.x > sGlobal->gameMap->getMapSize().width - 1
		|| targetTileCoord.y < 0
		|| targetTileCoord.y > sGlobal->gameMap->getMapSize().height - 1)
	{
		return kWall;
	}

	//��ȡǽ�ڲ��Ӧ�����ͼ��ID
	int targetTileGID = sGlobal->gameMap->getWallLayer()->getTileGIDAt(targetTileCoord);

	//���ͼ��ID��Ϊ0����ʾ��ǽ
	if (targetTileGID) 
	{
		return kWall;
	}

	//��ȡ������Ӧ�����ͼ��ID
	targetTileGID = sGlobal->gameMap->getEnemyLayer()->getTileGIDAt(targetTileCoord);

	//���ͼ��ID��Ϊ0����ʾ�й���
	if (targetTileGID) 
	{
		//��ʼս��
		fight();
		return kEnemy;
	}

	//��ȡ��Ʒ���Ӧ�����ͼ��ID
	targetTileGID = sGlobal->gameMap->getItemLayer()->getTileGIDAt(targetTileCoord);

	//���ͼ��ID��Ϊ0����ʾ����Ʒ
	if (targetTileGID)
	{
		//ʰȡ��Ʒ
		pickUpItem();
		return kItem;
	}

	//��ȡ�Ų��Ӧ�����ͼ��ID
	targetTileGID = sGlobal->gameMap->getDoorLayer()->getTileGIDAt(targetTileCoord);

	//���ͼ��ID��Ϊ0����ʾ����
	if (targetTileGID)
	{
		//����
		openDoor(targetTileGID);
		return kDoor;
	}

	int index = targetTileCoord.x + targetTileCoord.y * sGlobal->gameMap->getMapSize().width;

	//��npc�ֵ��в�ѯ
	NPC *npc = sGlobal->gameMap->npcDict.at(index);
	if (npc != NULL)
	{
		actWithNPC();
		return kNPC;
	}

	//��Teleport�ֵ��в�ѯ
	Teleport *teleport = sGlobal->gameMap->teleportDict.at(index);
	if (teleport != NULL)
	{
		doTeleport(teleport);
		return kTeleport;
	}

	//����ͨ��
	return kNone;
}

//��ʼս��
void Hero::fight()
{
	//�Ѿ���ս���У������ظ�ս��
	if (isHeroFighting)
	{
		return;
	}

	isHeroFighting = true;

	//��ʾ�����ܵ������Ч��
	sGlobal->gameMap->showEnemyHitEffect(targetTileCoord);

	//��ʾ��ʧ������ֵ�����ü��������һ��
	char temp[30] = { 0 };
	sprintf(temp, "lost hp: -%d", 100);
	sGlobal->gameLayer->showTip(temp, getPosition());

	//��������ʾս�������ľ�������Ϊ�ɼ�
	fightSprite->setVisible(true);

	//������ʾս��������λ��Ϊ��ʿ�͹�����м��
	Point pos = Point((targetPosition.x - getPosition().x) / 2 + 16, (targetPosition.y - getPosition().y) / 2 + 16);
	fightSprite->setPosition(pos);

	//����ս������
	Action* action = Sequence::create(
		sAnimationMgr->createAnimate(aFight),
		CallFuncN::create(CC_CALLBACK_1(Hero::onFightDone, this)),
		NULL);

	fightSprite->runAction(action);
}

//ս�������Ļص�
void Hero::onFightDone(Node* pSender)
{
	//ɾ�������Ӧ��ͼ�飬��ʾ�Ѿ�������
	sGlobal->gameMap->getEnemyLayer()->removeTileAt(targetTileCoord);
	isHeroFighting = false;
}

//ʰȡ��Ʒ
void Hero::pickUpItem()
{
	//��ʾ��ʾ��Ϣ
	sGlobal->gameLayer->showTip("get an item, hp +100", this->getPosition());

	//����Ʒ�ӵ�ͼ���Ƴ�
	sGlobal->gameMap->getItemLayer()->removeTileAt(targetTileCoord);
}

//����
void Hero::openDoor(int gid)
{
	//��������ڱ��������򷵻�
	if (isDoorOpening)
	{
		return;
	}

	//�������ڱ��������ŵĳ�ʼGID
	targetDoorGID = gid;
	isDoorOpening = true;

	//��ʱ�������Ŷ���
	schedule(schedule_selector(Hero::updateOpenDoorAnimation), 0.1f);
}

//���¿��Ŷ���
void Hero::updateOpenDoorAnimation(float time)
{
	//���㶯����һ֡��ͼ��ID��TileMap��ͼ���ŷ�ʽ�Ǻ������1������ÿ����ͬ��λ�õ�ͼ��ID�����ÿ��ͼ��ĸ���
	int nextGID = sGlobal->gameMap->getDoorLayer()->getTileGIDAt(targetTileCoord) + 4;

	//��������˵���֡�������ͽ���ǰλ�õ�ͼ��ɾ������ȡ����ʱ��
	if (nextGID - targetDoorGID > 4 * 3) 
	{
		sGlobal->gameMap->getDoorLayer()->removeTileAt(targetTileCoord);
		unschedule(schedule_selector(Hero::updateOpenDoorAnimation));
		isDoorOpening = false;
	}
	else
	{
		//���¶�������һ֡
		sGlobal->gameMap->getDoorLayer()->setTileGID(nextGID, targetTileCoord);
	}
}

//��NPC����
void Hero::actWithNPC()
{
	sGlobal->gameLayer->showTip("talking with npc", getPosition());
}

//���͵��߼�
void Hero::doTeleport(Teleport *teleport)
{
	//�Ӵ��͵�������к�ȥĿ���ͼ�Ĳ���
	sGlobal->currentLevel = teleport->targetMap;

	//��ȡ��ʿ���µ�ͼ�е���ʼλ��
	sGlobal->heroSpawnTileCoord = teleport->heroTileCoord;

	//��ʼ�л���Ϸ��ͼ
	sGlobal->gameScene->switchMap();
}
