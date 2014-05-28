#ifndef __EditScene_H__
#define __EditScene_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "cocos-ext.h"
#include "Rock.h"
#include "Map.h"
#include "obstacle.h"
#include "Bolloon.h"
#include "Data.h"
#include <iostream>
#include   <map> 
#define RATIO 48.0f
//必须使用这个cocos2d::extension命名空间来使用CCPhysicsSprite
USING_NS_CC_EXT;
USING_NS_CC;
 using   namespace   std; 
class EditScene : public cocos2d::CCLayer
{
	virtual bool init();  
	static cocos2d::CCScene* scene();
	    // implement the "static node()" method manually
    CREATE_FUNC(EditScene);
private:


};

#endif // __EditScene_H__
