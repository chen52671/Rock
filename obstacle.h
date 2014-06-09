#ifndef __obstacle_H__
#define __obstacle_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "cocos-ext.h"
#include "constant.h"

//����ʹ�����cocos2d::extension�����ռ���ʹ��CCPhysicsSprite
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


//�̳���CCPhysicsSprite�����Է���ĺ��������������

class obstacle : public CCPhysicsSprite
{

public:
	static obstacle* createObstacle(_obstacleType type,CCPoint pt,const b2Vec2& scale);//�������ʹ�����ͬ���ʵ��ϰ� //obsolete 
	//����һ���µĺ�����������״�����ʣ�λ�� ����һ��obstacle*����
	static obstacle* createObstacle(_drawShape obstacleShape,_drawMaterial obstacleMaterial,CCPoint obstaclePosition);
	bool isDead();
	void setRadius(float radius );
	CCPoint getobstaclePosition();
	bool containPoint(CCPoint pt);
	void setSelected(bool Selected);
	float radius;//�뾶 obsolete 
	_drawMaterial obstacleMaterial;
	_drawShape obstacleShape;
	CCPoint obstaclePosition;
	CCSize ObstacleSize;
	bool Selected;
	float obstacleAngle; //������ת�Ƕ�

	b2Vec2 scale;//slider ��x y �����ϵ�����ϵ�� 0-100
	b2Vec2 AdapterScale;//x y �����ϵ�����ϵ�� ������ϵ��Ϊscale*AdapterScale

	bool Dead;//��������ˣ���update��ɾ������
	float weight;
	enum _obstacleType obstacleType;//obsolete 
protected:



};

#endif // __obstacle_H__
