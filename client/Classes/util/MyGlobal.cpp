#include "MyGlobal.h"

DECLARE_SINGLETON_MEMBER(MyGlobal);

MyGlobal::MyGlobal(void)
{
	MygameScene = NULL;

	MygameLayer = NULL;

	MygameMap = NULL;

	Myhero = NULL;

	MycontrolLayer = NULL;
	//新游戏，当前地图层数为0
	currentLevel = 0;

	//勇士出生位置
	heroSpawnTileCoord = Point(8, 5);
}

MyGlobal::~MyGlobal(void)
{

}