#include "Bolloon.h"
#include "Box2D/Box2D.h"



Bolloon* Bolloon::createBolloon(CCPoint pt)
{


	Bolloon * mBolloon = new Bolloon();
	CCTexture2D *texturemBolloon = CCTextureCache::sharedTextureCache()->addImage("bollon.png");
	

	    if (mBolloon && mBolloon->initWithTexture(texturemBolloon))
    {
        mBolloon->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(mBolloon);
    }
	mBolloon->setScale(0.2);
	return mBolloon;
}

bool Bolloon::isDead()
{
	return true;
}