#ifndef __ROCK_H__
#define __ROCK_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "cocos-ext.h"
#define RATIO 48.0f
//必须使用这个cocos2d::extension命名空间来使用CCPhysicsSprite
USING_NS_CC_EXT;
USING_NS_CC;
//定义一个石球类，包含大小，重量等属性。每次点击一次屏幕，建立一个石球。
class Rock : public CCPhysicsSprite
{

public:
	static Rock* createRock(float dt,CCPoint pt);//根据时间创建不同大小的石球
	bool isDead();

protected:
	bool Dead;
	float size;//ratio
	float weight;


};

#endif // __ROCK_H__
