#ifndef __EditScene_H__
#define __EditScene_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "cocos-ext.h"

#include <iostream>
#define RATIO 48.0f
//必须使用这个cocos2d::extension命名空间来使用CCPhysicsSprite
USING_NS_CC_EXT;
USING_NS_CC;
using   namespace   std; 
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


class MenuLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();  
	CREATE_FUNC(MenuLayer);
	_drawMaterial drawMaterial;
	
	void MetalSetting(CCObject* pSender);
	void GlassSetting(CCObject* pSender);
	void WoodSetting(CCObject* pSender);
protected:
	CCMenuItemImage *mMetal;
	CCMenuItemImage *mGlass;
	CCMenuItemImage *mWood;
	
};

class EditScene : public cocos2d::CCLayer
{
public:
	virtual bool init();  
	static cocos2d::CCScene* scene();
	// implement the "static node()" method manually
	CREATE_FUNC(EditScene);


	void rectangleSetting(CCObject* pSender);
	void circleSetting(CCObject* pSender);
	void triangleSetting(CCObject* pSender);
	// a selector callback
	virtual void menuCloseCallback(cocos2d::CCObject* pSender);
	MenuLayer *menuLayer;
protected:
	CCMenuItemImage *mRectangle_D;
	CCMenuItemImage *mCircle_D;
	CCMenuItemImage *mTriangle_D;
	_drawShape drawShape;
	

};



#endif // __EditScene_H__
