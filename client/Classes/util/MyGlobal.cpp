#include "MyGlobal.h"

DECLARE_SINGLETON_MEMBER(MyGlobal);

MyGlobal::MyGlobal(void)
{
	MygameScene = NULL;

	MygameLayer = NULL;

	MygameMap = NULL;

	Myhero = NULL;

	MycontrolLayer = NULL;
	//����Ϸ����ǰ��ͼ����Ϊ0
	currentLevel = 0;

	//��ʿ����λ��
	heroSpawnTileCoord = Point(8, 5);
}

MyGlobal::~MyGlobal(void)
{

}