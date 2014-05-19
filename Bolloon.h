#ifndef __Bolloon_H__
#define __Bolloon_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "cocos-ext.h"
#include "constant.h"


USING_NS_CC_EXT;
USING_NS_CC;

class Bolloon : public CCPhysicsSprite
{

public:
	static Bolloon* createBolloon(CCPoint pt);//����ʱ�䴴����ͬ��С��ʯ��
	bool isDead();
		float radius;
protected:
	bool Dead;

	float weight;


};

#endif // __Bolloon_H__
