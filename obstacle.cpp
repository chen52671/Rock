#include "obstacle.h"
#include "Box2D/Box2D.h"

obstacle* obstacle::createObstacle(_drawShape obstacleShape,_drawMaterial obstacleMaterial,CCPoint obstaclePosition)
{
	CCTexture2D *textureobstacle;
	obstacle * m_obstacle = new obstacle();
	//根据参数创建一个基本的图形
	textureobstacle = CCTextureCache::sharedTextureCache()->addImage("glass1.png"); //创建texture这块待修改。

	CCSize size = textureobstacle->getContentSize();//图片大小

	if (m_obstacle && m_obstacle->initWithTexture(textureobstacle))
	{
		m_obstacle->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(m_obstacle);
	}

	m_obstacle->ObstacleSize = m_obstacle->getContentSize();
	m_obstacle->obstaclePosition = obstaclePosition;
	m_obstacle->obstacleShape =obstacleShape; 
	m_obstacle->obstacleMaterial =obstacleMaterial;
	m_obstacle->Selected = false;
	return m_obstacle;
}

obstacle* obstacle::createObstacle(_obstacleType type,CCPoint pt,const b2Vec2& scale)
{

	CCTexture2D *textureobstacle;
	obstacle * m_obstacle = new obstacle();
	switch (type)
	{
	case glassTube://玻璃材质1,方块
		textureobstacle = CCTextureCache::sharedTextureCache()->addImage("glass1.png");
		break;
	case glassRectangle://玻璃材质2，长条
		textureobstacle = CCTextureCache::sharedTextureCache()->addImage("glass2.png");
		break;
	case woodTube:
		textureobstacle = CCTextureCache::sharedTextureCache()->addImage("wood1.png");
		break;
	case woodRectangle:
		textureobstacle = CCTextureCache::sharedTextureCache()->addImage("wood2.png");
		break;
	case metalTube:
		textureobstacle = CCTextureCache::sharedTextureCache()->addImage("metal1.png");
		break;
	case metalRectangle:
		textureobstacle = CCTextureCache::sharedTextureCache()->addImage("metal2.png");
		break;
	default:
		textureobstacle = CCTextureCache::sharedTextureCache()->addImage("glass2.png");
		break;
	}



	if (m_obstacle && m_obstacle->initWithTexture(textureobstacle))
	{
		m_obstacle->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(m_obstacle);
	}
	m_obstacle->setScaleX(scale.x);
	m_obstacle->setScaleY(scale.y);



	return m_obstacle;
}
void  obstacle::setRadius(float radius )
{
	this->radius=radius;
}
bool obstacle::isDead()
{
	return true;
}

CCPoint obstacle::getobstaclePosition()
{
	return this->obstaclePosition;
}

//检测该点是否包含在该物体内部？
bool obstacle::containPoint(CCPoint pt)
{
	if(pt.x>obstaclePosition.x-ObstacleSize.width/2 && pt.x<obstaclePosition.x+ObstacleSize.width/2 && pt.y>obstaclePosition.y-ObstacleSize.height/2&& pt.y<obstaclePosition.y+ObstacleSize.height/2)
	return true;
	else 
	return false;
}

void obstacle::setSelected()
{
	this->Selected = true;
}