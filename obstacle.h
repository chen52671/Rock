#ifndef __obstacle_H__
#define __obstacle_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "cocos-ext.h"
#include "constant.h"

//必须使用这个cocos2d::extension命名空间来使用CCPhysicsSprite
USING_NS_CC_EXT;
USING_NS_CC;
//obsolete 
enum _obstacleType{
	woodTube,
	woodRectangle,
	glassTube,
	glassRectangle,
	metalTube,
	metalRectangle

};
enum _drawShape{
	RECTANGLE,
	CIRLE,
	TRIANGLE
};
enum _drawMaterial{
	METAL,
	GLASS,
	WOOD
};


//继承自CCPhysicsSprite，可以方便的和物理世界关联。

class obstacle : public CCPhysicsSprite
{

public:
	static obstacle* createObstacle(_obstacleType type,CCPoint pt,const b2Vec2& scale);//根据类型创建不同材质的障碍 //obsolete 
	//重载一个新的函数，根据形状，材质，位置 创建一个obstacle*对象。
	static obstacle* createObstacle(_drawShape obstacleShape,_drawMaterial obstacleMaterial,CCPoint obstaclePosition);
	bool isDead();
	void setRadius(float radius );
	CCPoint getobstaclePosition();
	bool containPoint(CCPoint pt);
	void setSelected(bool Selected);
	float radius;//半径 obsolete 
	_drawMaterial obstacleMaterial;
	_drawShape obstacleShape;
	CCPoint obstaclePosition;
	CCSize ObstacleSize;
	bool Selected;
	float obstacleAngle; //物体旋转角度

	b2Vec2 scale;//slider 在x y 方向上的缩放系数 0-100
	b2Vec2 AdapterScale;//x y 方向上的适配系数 总缩放系数为scale*AdapterScale

	bool Dead;//如果死掉了，从update中删除掉。
	float weight;
	enum _obstacleType obstacleType;//obsolete 
protected:



};

#endif // __obstacle_H__
