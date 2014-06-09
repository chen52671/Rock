#include "obstacle.h"
#include "Box2D/Box2D.h"

obstacle* obstacle::createObstacle(_drawShape obstacleShape,_drawMaterial obstacleMaterial,CCPoint obstaclePosition)
{
	CCTexture2D *textureobstacle;
	obstacle * m_obstacle = new obstacle();
	//���ݲ�������һ��������ͼ�Σ�9�� case��
	//ͼƬ��������scaleϵ�������ġ�һ����slider��ϵ����Ĭ��ͼƬ150*150��sliderϵ��Ϊ50%
	//��һ��ϵ��Ϊ������ͼƬΪ�������ֻ���Ļ������ϵ������ʱ��Ϊ100. ���ڸ�����ͼ�������޸ġ�
	//�Ժ��ͼƬ������ߣ�Ȼ���趨����ϵ��Ϊ50.����ʼ���õ�ͼƬ�������ź��ͼƬ��Ϊ�����Ŵ����¿ռ�
	switch(obstacleShape)
	{
	case RECTANGLE:
		if( obstacleMaterial == METAL)
		{
			textureobstacle = CCTextureCache::sharedTextureCache()->addImage("MetalRectangle.png"); 
		}
		else if ( obstacleMaterial == GLASS)
		{
			textureobstacle = CCTextureCache::sharedTextureCache()->addImage("GlassRectangle.png"); 
		}
		else if (obstacleMaterial == WOOD)
		{
			textureobstacle = CCTextureCache::sharedTextureCache()->addImage("WoodRectangle.png");
		}
		break;
	case CIRLE:
		if( obstacleMaterial == METAL)
		{
			textureobstacle = CCTextureCache::sharedTextureCache()->addImage("MetalCircle.png"); 
		}
		else if ( obstacleMaterial == GLASS)
		{
			textureobstacle = CCTextureCache::sharedTextureCache()->addImage("GlassCircle.png"); 
		}
		else if (obstacleMaterial == WOOD)
		{
			textureobstacle = CCTextureCache::sharedTextureCache()->addImage("WoodCircle.png"); 
		}
		break;
	case TRIANGLE:
		if( obstacleMaterial == METAL)
		{
			textureobstacle = CCTextureCache::sharedTextureCache()->addImage("MetalTriangle.png"); 
		}
		else if ( obstacleMaterial == GLASS)
		{
			textureobstacle = CCTextureCache::sharedTextureCache()->addImage("GlassTriangle.png"); 
		}
		else if (obstacleMaterial == WOOD)
		{
			textureobstacle = CCTextureCache::sharedTextureCache()->addImage("WoodTriangle.png"); 
		}
		break;
	default:
		break;
	}


	CCSize size = textureobstacle->getContentSize();//ͼƬ��С�����ֻ������δ�С��
	//���� 150*200 Բ�� 150*150 �����α߳�200

	if (m_obstacle && m_obstacle->initWithTexture(textureobstacle))
	{
		m_obstacle->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(m_obstacle);
	}
	//��ʼ���������ĸ���ֵ��
	m_obstacle->ObstacleSize = size;
	m_obstacle->obstaclePosition = obstaclePosition;
	m_obstacle->obstacleShape =obstacleShape; 
	m_obstacle->obstacleMaterial =obstacleMaterial;
	m_obstacle->Selected = false;


	m_obstacle->obstacleAngle = 0; //������ת�Ƕ�
	m_obstacle->scale.x=50;//x y �����ϵ�����ϵ�� 0-100
	m_obstacle->scale.y=50;//��ʼΪ50
	m_obstacle->Dead = false;//��������ˣ���update��ɾ������
	m_obstacle->weight = 0;


	m_obstacle->setScaleX(m_obstacle->scale.x/100);
	m_obstacle->setScaleY(m_obstacle->scale.y/100);
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
	if(pt.x>obstaclePosition.x-(ObstacleSize.width/2)*(scale.x/100) && pt.x<obstaclePosition.x+(ObstacleSize.width/2)*(scale.x/100) && pt.y>obstaclePosition.y-(ObstacleSize.height/2)*(scale.y/100)&& pt.y<obstaclePosition.y+(ObstacleSize.height/2)*(scale.y/100))
		return true;
	else 
		return false;
}

void obstacle::setSelected(bool Selected)
{

	this->Selected = Selected;
}