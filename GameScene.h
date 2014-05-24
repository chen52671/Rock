#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "cocos-ext.h"
#include "Rock.h"
#include "Map.h"
#include "obstacle.h"
#include "Bolloon.h"

#include <iostream>
#include   <map> 
#define RATIO 48.0f
//必须使用这个cocos2d::extension命名空间来使用CCPhysicsSprite
USING_NS_CC_EXT;
USING_NS_CC;
 using   namespace   std; 
class GameScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);

	 void updateGame(float dt);
	//重写触屏方法
	virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	//获取时间
	long getCurrentTime();   


	CCActionInterval*  actionTo;
	Rock *mRock;

	b2World *world;
	CCSprite *fakeRock;
    CCSize screenSize;
	CCPoint touchPoint;
	long beginTime;
	long endTime;
	double mscale;
	bool rockgrowing;
	Map *mMap;
	Bolloon *mbolloon;
	float rockMassTotal;
	double  rockPercent;
	map<int ,obstacle*> mObstacles;
	CCLabelTTF* rockPercentLabel;
private:

	void addObstacle(int type,CCPoint pt,float angle,const b2Vec2& scale,int key);
	void addRock(float dt,CCPoint pt,float scale);
	void addMap();
	void initWorld();
	void addBolloon(CCPoint pt);
	void stopGame();
	void showEndMenu();
	void onQuit(CCObject* sender);
	void onRestart(CCObject* sender);
	void onNext(CCObject* sender);
	void addRockPercent();
};

#endif // __GameScene_H__
