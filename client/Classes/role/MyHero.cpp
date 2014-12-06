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

	//�����������߶����ĵ�һ֡��������spriteWithSpriteFrame
	heroSprite = Sprite::createWithSpriteFrame(sAnimationMgr->getAnimation(kRight)->getFrames().at(0)->getSpriteFrame());

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

void MyHero::move(HeroDirection direction) 
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

	//heroSprite���������߶���
	heroSprite->runAction(sAnimationMgr->createAnimate(direction));

	//�������λ�ƣ�����ʱ����onMoveDone���� �ѷ�����Ϣ���ݸ�onMoveDone����
	Action *action = Sequence::create(
		MoveBy::create(0.20f, moveByPosition), 
		CallFuncN::create(CC_CALLBACK_1(MyHero::onMoveDone, this, (void*)direction)), 
		NULL);

	this->runAction(action);

	isHeroMoving = true;
}

void MyHero::onMoveDone(Node* pTarget, void* data)
{
	//��void*��ת��Ϊint���ٴ�intת����ö������
	int direction = (int) data;
	setFaceDirection((HeroDirection)direction);
	isHeroMoving = false;
	sGlobal->gameLayer->setSceneScrollPosition(this->getPosition());
}

void MyHero::setFaceDirection(HeroDirection direction)
{
	heroSprite->setTextureRect(Rect(0, 32*direction, 32, 32));
}

