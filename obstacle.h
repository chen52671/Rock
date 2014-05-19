#ifndef __obstacle_H__
#define __obstacle_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "cocos-ext.h"
#include "constant.h"

//����ʹ�����cocos2d::extension�����ռ���ʹ��CCPhysicsSprite
USING_NS_CC_EXT;
USING_NS_CC;

class obstacle : public CCPhysicsSprite
{

public:
	static obstacle* createObstacle(int type,CCPoint pt,const b2Vec2& scale);//�������ʹ�����ͬ���ʵ��ϰ�
	bool isDead();
	void setRadius(float radius );
	float radius;//ratio
protected:
	bool Dead;
	float weight;


};

#endif // __obstacle_H__
