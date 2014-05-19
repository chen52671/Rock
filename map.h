#ifndef __MAP_H__
#define __MAP_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "cocos-ext.h"
#include "constant.h"
//必须使用这个cocos2d::extension命名空间来使用CCPhysicsSprite
USING_NS_CC_EXT;
USING_NS_CC;

//定义一个地图类，包含添加背景框，添加物体。
class Map : public CCPhysicsSprite
{

public:
	void addBackgrondBox();
	void addMap();
	static Map* creatAndInit(b2World *world);
protected:
	//创建一个保存石头，木头等障碍物的map
	map<int,CCPhysicsSprite> barrier;
	b2World *world;


};

#endif // __MAP_H__
