#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "cocos-ext.h"
#include "Rock.h"
#define RATIO 48.0f
//必须使用这个cocos2d::extension命名空间来使用CCPhysicsSprite
USING_NS_CC_EXT;
USING_NS_CC;
class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	virtual void update(float dt);
	//重写触屏方法
	virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	//获取时间
	long getCurrentTime();   



	Rock *mRock;

	b2World *world;
    CCPhysicsSprite *bird;
    CCSize screenSize;
	CCPoint touchPoint;
	long beginTime;
	long endTime;
	long mscale;

private:

    void addBird();
	void addRock(float dt,CCPoint pt);
	void addMap();
	void initWorld();
};

#endif // __HELLOWORLD_SCENE_H__
