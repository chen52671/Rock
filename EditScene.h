#ifndef __EditScene_H__
#define __EditScene_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "cocos-ext.h"
#include "MySlider.h"
#include "obstacle.h"
#include <iostream>

#define RATIO 48.0f
//必须使用这个cocos2d::extension命名空间来使用CCPhysicsSprite
USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;//使用slider插件
using   namespace   std; 


class MenuLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();  
	CREATE_FUNC(MenuLayer);
	_drawMaterial drawMaterial;


	void MetalSettingR(CCObject* pSender);
	void GlassSettingR(CCObject* pSender);
	void WoodSettingR(CCObject* pSender);
	void MetalSettingC(CCObject* pSender);
	void GlassSettingC(CCObject* pSender);
	void WoodSettingC(CCObject* pSender);
	void MetalSettingT(CCObject* pSender);
	void GlassSettingT(CCObject* pSender);
	void WoodSettingT(CCObject* pSender);
	void showRec();
	void showCircle();
	void showTriangle();
protected:
	CCMenuItemImage *mMetal_R;
	CCMenuItemImage *mGlass_R;
	CCMenuItemImage *mWood_R;
	CCMenuItemImage *mMetal_C;
	CCMenuItemImage *mGlass_C;
	CCMenuItemImage *mWood_C;
	CCMenuItemImage *mMetal_T;
	CCMenuItemImage *mGlass_T;
	CCMenuItemImage *mWood_T;

};

class EditScene : public cocos2d::CCLayer
{
public:

	EditScene();
	~EditScene();

	virtual bool init();  
	static cocos2d::CCScene* scene();
	// implement the "static node()" method manually
	CREATE_FUNC(EditScene);


	void rectangleSetting(CCObject* pSender);
	void circleSetting(CCObject* pSender);
	void triangleSetting(CCObject* pSender);
	// a selector callback
	virtual void menuBackCallback(cocos2d::CCObject* pSender);
	//重写触屏方法
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	
	void updateGame(float dt);
	void addSliders();
	void sliderEvent(CCObject* pSender, SliderEventType type);
	void sliderEvent2(CCObject* pSender, SliderEventType type);
	
	void initWorld();
	void addObstacle(obstacle* mObstacle);
	b2World *world;
	CCPoint origin;
	CCSize visibleSize;
protected:
	CCMenuItemImage *mRectangle_D;
	CCMenuItemImage *mCircle_D;
	CCMenuItemImage *mTriangle_D;
	_drawShape drawShape;
	UILayer *m_pUiLayer;
	UILabel* m_pDisplayValueLabel_H;
	UILabel* m_pDisplayValueLabel_V;
	MenuLayer*menuLayer;
	CCArray *_Obstacle; //保存所有障碍物的数组

};



#endif // __EditScene_H__
