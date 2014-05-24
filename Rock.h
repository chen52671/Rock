#ifndef __ROCK_H__
#define __ROCK_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "cocos-ext.h"
#include "constant.h"

//����ʹ�����cocos2d::extension�����ռ���ʹ��CCPhysicsSprite
USING_NS_CC_EXT;
USING_NS_CC;
//����һ��ʯ���࣬������С�����������ԡ�ÿ�ε��һ����Ļ������һ��ʯ��
class Rock : public CCPhysicsSprite
{

public:
	static Rock* createRock(float dt,CCPoint pt,float scale);//����ʱ�䴴����ͬ��С��ʯ��
	bool isDead();
	void setRadius(float radius );
	float radius;//ratio
		float weight;
protected:
	bool Dead;
	



};

#endif // __ROCK_H__
