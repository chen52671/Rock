#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    mscale=0.2;
	screenSize = CCDirector::sharedDirector()->getVisibleSize();
	//开启触摸
	setTouchEnabled(true);
    //1 初始化物理世界
    initWorld();
	//2 加载地图。
	addMap();
	mRock =new Rock();
	//
	scheduleUpdate();
 
   
    return true;
}

void HelloWorld::initWorld(){
    world = new b2World(b2Vec2(0, -10));

}
void  HelloWorld::addMap()
{
	

}
void HelloWorld::registerWithTouchDispatcher()
{
    // higher priority than dragging
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, -10, true);
}
 bool HelloWorld::ccTouchBegan(CCTouch* touch, CCEvent* event)
	{
	CCPoint touchLocation = touch->getLocation();    

    touchPoint = convertToNodeSpace( touchLocation );
		beginTime=getCurrentTime();
	//画一个最小的rock
	//在之后每一帧，rock放大一点点
	//直到ccTouchEnded，停止放大，然后绑定一个box2d对象。
		mRock =Rock::createRock(0,touchPoint);

		return true;
	}
void HelloWorld::ccTouchEnded(CCTouch* touch, CCEvent* event)
	{
			//获取松开时间
	endTime=getCurrentTime();
	//添加rock精灵
	addRock(endTime-beginTime,touchPoint);
	}




long HelloWorld::getCurrentTime()    
{     
    struct cc_timeval tv;     
    CCTime::gettimeofdayCocos2d(&tv, NULL);  
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;     
}   

void HelloWorld::addRock(float dt,CCPoint pt)
{

	Rock *rock= Rock::createRock(dt,pt);
	
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2(pt.x/RATIO, pt.y/RATIO);
    b2Body * rockBody = world->CreateBody(&bodyDef);

	rock->setPTMRatio(RATIO);
    rock->setB2Body(rockBody);
	rock->setPosition(ccp( pt.x, pt.y));
    addChild(rock);

}

void HelloWorld::addBird(){
    
    bird = CCPhysicsSprite::create("bird.png");
    CCSize size = bird->getContentSize();
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2(screenSize.width/2/RATIO, screenSize.height/2/RATIO);
    b2Body * birdBody = world->CreateBody(&bodyDef);
    
    b2PolygonShape birdShape;
    birdShape.SetAsBox(size.width/2/RATIO, size.height/2/RATIO);
    
    b2FixtureDef birdFixtureDef;
    birdFixtureDef.shape= &birdShape;
    birdBody->CreateFixture(&birdFixtureDef);
    
    bird->setPTMRatio(RATIO);
    bird->setB2Body(birdBody);
    addChild(bird);
}

void HelloWorld::update(float dt){
	mscale=mscale*1.1;

    world->Step(dt, 8, 3);

}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
