#include "Rock.h"
#include "Box2D/Box2D.h"



Rock* Rock::createRock(float dt,CCPoint pt)
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
	rock->setScale( 0.2 );
	return rock;
}

bool Rock::isDead()
{
	return true;
}