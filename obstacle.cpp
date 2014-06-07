#include "obstacle.h"
#include "Box2D/Box2D.h"

obstacle* obstacle::createObstacle(_drawShape obstacleShape,_drawMaterial obstacleMaterial,CCPoint obstaclePosition)
{
	CCTexture2D *textureobstacle;
	obstacle * m_obstacle = new obstacle();
	//���ݲ�������һ��������ͼ��
	textureobstacle = CCTextureCache::sharedTextureCache()->addImage("glass1.png"); //����texture�����޸ġ�

	CCSize size = textureobstacle->getContentSize();//ͼƬ��С

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
	case glassTube://��������1,����
		textureobstacle = CCTextureCache::sharedTextureCache()->addImage("glass1.png");
		break;
	case glassRectangle://��������2������
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

//���õ��Ƿ�����ڸ������ڲ���
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