#include "obstacle.h"
#include "Box2D/Box2D.h"



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