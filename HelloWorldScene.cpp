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
	mscale = 0.01f;
	rockgrowing=false;
	screenSize = CCDirector::sharedDirector()->getVisibleSize();
	//��������
	setTouchEnabled(true);
	//1 ��ʼ����������
	initWorld();
	//2 ���ص�ͼ��
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
	//��һ����С��fakeRock
	//��֮��ÿһ֡��rock�Ŵ�һ���
	//ֱ��ccTouchEnded��ֹͣ�Ŵ�Ȼ���һ��box2d����
	fakeRock = CCSprite::create("rock.png");
	fakeRock->setPosition(ccp( touchPoint.x, touchPoint.y));
	fakeRock->setScale(mscale);

	//���ӵ���
	addChild(fakeRock);
	//����scale������
	actionTo = CCScaleTo::create(5.0f, 0.15f);	
	fakeRock->runAction( actionTo);
	rockgrowing=true;
	return true;
}
void HelloWorld::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	rockgrowing=false;
	fakeRock->stopAction(actionTo);
	float scale1=fakeRock->getScale();
	//ɾ��fakerock
	removeChild(fakeRock);
	//��ȡ�ɿ�ʱ��
	endTime=getCurrentTime();

	//����rock����
	addRock(endTime-beginTime,touchPoint,scale1);
}




long HelloWorld::getCurrentTime()    
{     
	struct cc_timeval tv;     
	CCTime::gettimeofdayCocos2d(&tv, NULL);  
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;     
}   

void HelloWorld::addRock(float dt,CCPoint pt,float scale)
{
		mRock =Rock::createRock(0,touchPoint,scale);
	
	//��С��Ž���
	
	
	

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(pt.x/RATIO, pt.y/RATIO);
	b2Body * rockBody = world->CreateBody(&bodyDef);

	mRock->setPTMRatio(RATIO);
	mRock->setB2Body(rockBody);
	mRock->setPosition(ccp( pt.x, pt.y));
	addChild(mRock);

}



void HelloWorld::update(float dt){
	if(rockgrowing)
	{
		//mscale*=1.03;
		//mRock->setScale( mscale );
	}


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