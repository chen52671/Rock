#ifndef __MAP_H__
#define __MAP_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "cocos-ext.h"
#include "constant.h"
//����ʹ�����cocos2d::extension�����ռ���ʹ��CCPhysicsSprite
USING_NS_CC_EXT;
USING_NS_CC;

//����һ����ͼ�࣬������ӱ�����������塣
class Map : public CCPhysicsSprite
{

public:
	void addBackgrondBox();
	void addMap();
	static Map* creatAndInit(b2World *world);
protected:
	//����һ������ʯͷ��ľͷ���ϰ����map
	map<int,CCPhysicsSprite> barrier;
	b2World *world;


};

#endif // __MAP_H__
