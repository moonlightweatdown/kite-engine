#include "MyGameMap.h"

MyGameMap::MyGameMap(void)
{
	MysGlobal->MygameMap = this;
}

MyGameMap::~MyGameMap(void)
{
	this->unscheduleAllSelectors();
}

//��̬��������������GameMapʵ��
MyGameMap* MyGameMap::gameMapWithTMXFile(const char *tmxFile)
{
	//newһ������
	MyGameMap *pRet = new MyGameMap();

	//����init����
	if (pRet->initWithTMXFile(tmxFile))
	{
		//���ö����init����
		pRet->extraInit();
		//��ʵ������autorelease�أ�ͳһ��������ƶ������������
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

//��cocos2d-x����ת��ΪTilemap����
Point MyGameMap::tileCoordForPosition(Point position)
{
	int x = position.x / this->getTileSize().width;
	int y = (((this->getMapSize().height - 1) * this->getTileSize().height) - position.y) / this->getTileSize().height;
	return Point(x, y);
}

//��Tilemap����ת��Ϊcocos2d-x����
Point MyGameMap::positionForTileCoord(Point tileCoord)
{
	Point pos = Point((tileCoord.x * this->getTileSize().width), ((this->getMapSize().height - tileCoord.y - 1) * this->getTileSize().height));
	return pos;
}
//TliedMap����ĳ�ʼ������
void MyGameMap::extraInit()
{
	//��������ͼ����������
	enableAnitiAliasForEachLayer();

	//��ʼ���������
	noLayer = this->getLayer("no");
	canLayer = this->getLayer("can");
	noLayer ->setVisible(false);
	canLayer ->setVisible(false);
	initObject();
}
//��ʼ�������
void MyGameMap::initObject()
{
	//��ȡ�����
	TMXObjectGroup* group = this->objectGroupNamed("object");

	//��ȡ������ڵ����ж���
	const ValueVector &objects = group->getObjects();

	//�������ж���
	for(ValueVector::const_iterator it = objects.begin(); 
		it != objects.end(); it++) 
	{
		const ValueMap &dict = (*it).asValueMap();

		std::string key = "x";

		//��ȡx����
		int x = dict.at(key).asInt();
		key = "y";

		//��ȡy����
		int y = dict.at(key).asInt();
		Point tileCoord = tileCoordForPosition(Point(x, y));

		//����ΨһID
		int index = tileCoord.x + tileCoord.y * this->getMapSize().width;
		key = "type";

		//��ȡ�������
		std::string type = dict.at(key).asString();

		//��������Ǵ�����
		if (type == "teleport")
		{
			MyTeleport *teleport = new MyTeleport(dict, x, y);
			myteleportDict.insert(index, teleport);
		}
	}
}
void MyGameMap::enableAnitiAliasForEachLayer()
{
	const Vector<Node *>&  childrenArray = this->getChildren();

	//����Tilemap������ͼ��
	for (size_t i = 0, count = childrenArray.size(); i < count; i++)
	{
		SpriteBatchNode* child = (SpriteBatchNode*)childrenArray.at(i);

		if (!child)
		{
			break;
		}

		//��ͼ��������������
		child->getTexture()->setAntiAliasTexParameters();
	}
}
