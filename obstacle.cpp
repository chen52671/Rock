#include "obstacle.h"
#include "Box2D/Box2D.h"

obstacle* obstacle::createObstacle(_drawShape obstacleShape,_drawMaterial obstacleMaterial,CCPoint obstaclePosition)
{
	CCTexture2D *textureobstacle;
	obstacle * m_obstacle = new obstacle();
	//根据参数创建一个基本的图形，9中 case。
	//图片是由两个scale系数决定的。一个是slider的系数。默认图片150*150，slider系数为50%
	//另一个系数为高清晰图片为了适配手机屏幕的缩放系数。暂时设为100. 后期根据贴图质量再修改。
	//以后把图片质量提高，然后设定适配系数为50.即初始放置的图片就是缩放后的图片。为后续放大留下空间
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


	CCSize size = textureobstacle->getContentSize();//图片大小，这个只是其矩形大小。
	//矩形 150*200 圆形 150*150 三角形边长200

	if (m_obstacle && m_obstacle->initWithTexture(textureobstacle))
	{
		m_obstacle->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(m_obstacle);
	}
	//初始化物体对象的各种值。
	m_obstacle->ObstacleSize = size;
	m_obstacle->obstaclePosition = obstaclePosition;
	m_obstacle->obstacleShape =obstacleShape; 
	m_obstacle->obstacleMaterial =obstacleMaterial;
	m_obstacle->Selected = false;


	m_obstacle->obstacleAngle = 0; //物体旋转角度
	m_obstacle->scale.x=50;//x y 方向上的缩放系数 0-100
	m_obstacle->scale.y=50;//初始为50
	m_obstacle->Dead = false;//如果死掉了，从update中删除掉。
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
	if(pt.x>obstaclePosition.x-(ObstacleSize.width/2)*(scale.x/100) && pt.x<obstaclePosition.x+(ObstacleSize.width/2)*(scale.x/100) && pt.y>obstaclePosition.y-(ObstacleSize.height/2)*(scale.y/100)&& pt.y<obstaclePosition.y+(ObstacleSize.height/2)*(scale.y/100))
		return true;
	else 
		return false;
}

void obstacle::setSelected(bool Selected)
{

	this->Selected = Selected;
}