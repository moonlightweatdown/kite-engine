#include "MyGameMap.h"

MyGameMap::MyGameMap(void)
{
	MysGlobal->MygameMap = this;
}

MyGameMap::~MyGameMap(void)
{
	this->unscheduleAllSelectors();
}

//静态方法，用于生成GameMap实例
MyGameMap* MyGameMap::gameMapWithTMXFile(const char *tmxFile)
{
	//new一个对象
	MyGameMap *pRet = new MyGameMap();

	//调用init方法
	if (pRet->initWithTMXFile(tmxFile))
	{
		//调用额外的init方法
		pRet->extraInit();
		//将实例放入autorelease池，统一由引擎控制对象的生命周期
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

//从cocos2d-x坐标转换为Tilemap坐标
Point MyGameMap::tileCoordForPosition(Point position)
{
	int x = position.x / this->getTileSize().width;
	int y = (((this->getMapSize().height - 1) * this->getTileSize().height) - position.y) / this->getTileSize().height;
	return Point(x, y);
}

//从Tilemap坐标转换为cocos2d-x坐标
Point MyGameMap::positionForTileCoord(Point tileCoord)
{
	Point pos = Point((tileCoord.x * this->getTileSize().width), ((this->getMapSize().height - tileCoord.y - 1) * this->getTileSize().height));
	return pos;
}
//TliedMap额外的初始化方法
void MyGameMap::extraInit()
{
	//开启各个图层的纹理抗锯齿
	enableAnitiAliasForEachLayer();

	//初始化各层对象
	noLayer = this->getLayer("no");
	canLayer = this->getLayer("can");
	noLayer ->setVisible(false);
	canLayer ->setVisible(false);
	initObject();
}
//初始化对象层
void MyGameMap::initObject()
{
	//获取对象层
	TMXObjectGroup* group = this->objectGroupNamed("object");

	//获取对象层内的所有对象
	const ValueVector &objects = group->getObjects();

	//遍历所有对象
	for(ValueVector::const_iterator it = objects.begin(); 
		it != objects.end(); it++) 
	{
		const ValueMap &dict = (*it).asValueMap();

		std::string key = "x";

		//获取x坐标
		int x = dict.at(key).asInt();
		key = "y";

		//获取y坐标
		int y = dict.at(key).asInt();
		Point tileCoord = tileCoordForPosition(Point(x, y));

		//计算唯一ID
		int index = tileCoord.x + tileCoord.y * this->getMapSize().width;
		key = "type";

		//获取对象类别
		std::string type = dict.at(key).asString();

		//如果类型是传送门
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

	//遍历Tilemap的所有图层
	for (size_t i = 0, count = childrenArray.size(); i < count; i++)
	{
		SpriteBatchNode* child = (SpriteBatchNode*)childrenArray.at(i);

		if (!child)
		{
			break;
		}

		//给图层的纹理开启抗锯齿
		child->getTexture()->setAntiAliasTexParameters();
	}
}
