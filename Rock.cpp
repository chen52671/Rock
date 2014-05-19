#include "Rock.h"
#include "Box2D/Box2D.h"



Rock* Rock::createRock(float dt,CCPoint pt,float scale)
{

	CCRect rect = CCRect(pt.x, pt.y, 2, 2);
	CCSize size =rect.size;
	Rock * rock = new Rock();
	CCTexture2D *textureRock = CCTextureCache::sharedTextureCache()->addImage("rock.png");
	

	    if (rock && rock->initWithTexture(textureRock))
    {
        rock->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(rock);
    }
	rock->setScale(scale);
	
	

	return rock;
}
void  Rock::setRadius(float radius )
{
	this->radius=radius;
}
bool Rock::isDead()
{
	return true;
}