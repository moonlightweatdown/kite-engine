#include "MyHero.h"

MyHero::MyHero()
{
	MysGlobal->Myhero = this;
}

MyHero::~MyHero()
{

}

bool MyHero::init()
{
	if (!Node::init())
	{
		return false;
	}

	//根据向下行走动画的第一帧创建精灵spriteWithSpriteFrame
	heroSprite = Sprite::createWithSpriteFrame(sAnimationMgr->getAnimation(kRight)->getFrames().at(0)->getSpriteFrame());

	//设置锚点
	heroSprite->setAnchorPoint(Point::ZERO);

	//将用于显示的heroSprite加到自己的节点下
	this->addChild(heroSprite);

	//创建空的战斗动画精灵
	fightSprite = Sprite::create();

	this->addChild(fightSprite);

	//一开始不处于move状态。
	isHeroMoving = false;
	isHeroFighting = false;
	isDoorOpening = false;
	return true;
}

void MyHero::move(HeroDirection direction) 
{
	if (isHeroMoving)
	{
		return;
	}

	//移动的距离
	Point moveByPosition;

	//根据方向计算移动的距离
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

	//计算目标坐标，用当前勇士坐标加上移动距离
	targetPosition = this->getPosition() + moveByPosition;
		//调用checkCollision检测碰撞类型，如果是墙壁、怪物、门，则只需要设置勇士的朝向
	CollisionType collisionType = checkCollision(targetPosition);

	if (collisionType == nogo)
	{
		setFaceDirection((HeroDirection)direction);
		return;
	}
	//heroSprite仅播放行走动画
	heroSprite->runAction(sAnimationMgr->createAnimate(direction));

	//主体进行位移，结束时调用onMoveDone方法 把方向信息传递给onMoveDone方法
	Action *action = Sequence::create(
		MoveBy::create(0.20f, moveByPosition), 
		CallFuncN::create(CC_CALLBACK_1(MyHero::onMoveDone, this, (void*)direction)), 
		NULL);

	this->runAction(action);

	isHeroMoving = true;
}

void MyHero::onMoveDone(Node* pTarget, void* data)
{
	//将void*先转换为int，再从int转换到枚举类型
	int direction = (int) data;
	setFaceDirection((HeroDirection)direction);
	isHeroMoving = false;
	MysGlobal->MygameLayer->setSceneScrollPosition(this->getPosition());
}

void MyHero::setFaceDirection(HeroDirection direction)
{
	heroSprite->setTextureRect(Rect(0, 32*direction, 32, 32));
}
//判断碰撞类型
CollisionType MyHero::checkCollision(Point heroPosition) 
{
	//cocos2d-x坐标转换为Tilemap坐标
	targetTileCoord = MysGlobal->MygameMap->tileCoordForPosition(heroPosition);

	//如果勇士坐标超过地图边界，返回kWall类型，阻止其移动
	if (heroPosition.x < 0
		|| targetTileCoord.x > MysGlobal->MygameMap->getMapSize().width - 1
		|| targetTileCoord.y < 0
		|| targetTileCoord.y > MysGlobal->MygameMap->getMapSize().height - 1)
	{
		return nogo;
	}
	int index = targetTileCoord.x + targetTileCoord.y * MysGlobal->MygameMap->getMapSize().width;

	//获取墙壁层对应坐标的图块ID
	int targetTileGID = MysGlobal->MygameMap->getNoLayer()->getTileGIDAt(targetTileCoord);

	//如果图块ID不为0，表示有墙
	if (targetTileGID) 
	{
		return nogo;
	}
	//从Teleport字典中查询
	MyTeleport *teleport = MysGlobal->MygameMap->myteleportDict.at(index);
	if (teleport != NULL)
	{
		doTeleport(teleport);
		return kTeleport;
	}
	//可以通行
	return kNone;
}
//传送点逻辑
void MyHero::doTeleport(MyTeleport *teleport)
{
	//从传送点的属性中后去目标地图的层数
	MysGlobal->currentLevel = teleport->targetMap;

	//获取勇士在新地图中的起始位置
	MysGlobal->heroSpawnTileCoord = teleport->heroTileCoord;

	//开始切换游戏地图
	MysGlobal->MygameScene->switchMap();
}


