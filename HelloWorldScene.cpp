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
	//��������ڵ�����
	addBolloon(ccp(200.0,60.0));
	//���ϰ�����
	addObstacle(0,ccp(140.0,80.0),b2_pi*0.5,b2Vec2(0.2f, 0.2f),0);
	addObstacle(1,ccp(200.0,100.0),0.0,b2Vec2(0.4f, 0.2f),1);
	addObstacle(0,ccp(260.0,80.0),b2_pi*0.5,b2Vec2(0.2f, 0.2f),2);
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
	 mMap=Map::creatAndInit(world);
	 mMap->addMap();


	 addChild(mMap);
}
void HelloWorld::addBolloon(CCPoint pt)
{
	mbolloon=Bolloon::createBolloon(pt);
	CCSize size = mbolloon->getContentSize();//2���뾶
	mbolloon->radius = (size.width*0.05)/RATIO;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.allowSleep = false;
	b2Body *  BolloonBody= world->CreateBody(&bodyDef);
	
	b2CircleShape BolloonShape;
	//�޸�Ϊ������Ĵ�С�ı�뾶
    BolloonShape.m_radius = mbolloon->radius;
    
    b2FixtureDef rockFixtureDef;
    rockFixtureDef.shape= &BolloonShape;
	rockFixtureDef.density=0.1;
	rockFixtureDef.restitution = 0.3f;//��������
	rockFixtureDef.friction=1.0f;



    BolloonBody->CreateFixture(&rockFixtureDef);
	mbolloon->setPTMRatio(RATIO);
	mbolloon->setB2Body(BolloonBody);
	mbolloon->setPosition(ccp( pt.x, pt.y));
	BolloonBody->ApplyForceToCenter(b2Vec2(0.0f, 0.1f));
	//test the mass
	b2MassData massData;
    BolloonBody->GetMassData(&massData);

	addChild(mbolloon);

}
void HelloWorld::addObstacle(int type,CCPoint pt,float angle,const b2Vec2& scale,int key)
{
	obstacle* mObstacle =obstacle::createObstacle(type,pt,scale);

	CCSize size = mObstacle->getContentSize();//2���뾶
	

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(pt.x/RATIO, pt.y/RATIO);
	bodyDef.allowSleep = true;
	bodyDef.angle =angle;


	b2Body *  ObstacleBody= world->CreateBody(&bodyDef);

	b2PolygonShape ObstacleShape;

    ObstacleShape.SetAsBox(size.width/2/RATIO*scale.x,size.height/2/RATIO*scale.y);
    
    b2FixtureDef rockFixtureDef;
    rockFixtureDef.shape= &ObstacleShape;
	rockFixtureDef.density=1;
	//rockFixtureDef.restitution = 0.3f;//��������
	rockFixtureDef.friction=1.0f;

    ObstacleBody->CreateFixture(&rockFixtureDef);

	mObstacle->setPTMRatio(RATIO);
	mObstacle->setB2Body(ObstacleBody);
	mObstacle->setPosition(ccp( pt.x, pt.y));
	addChild(mObstacle);

	//test the mass
	b2MassData massData;
	ObstacleBody->GetMassData(&massData);

	mObstacles.insert(make_pair(key,mObstacle));
}

void HelloWorld::addRock(float dt,CCPoint pt,float scale)
{
		mRock =Rock::createRock(0,pt,scale);
		//����С����������뾶
	CCSize size = mRock->getContentSize();//2���뾶
	mRock->setRadius(size.width/2/RATIO*scale);
	//��С��Ž���

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(pt.x/RATIO, pt.y/RATIO);
	bodyDef.allowSleep = true;
	b2Body *  rockBody= world->CreateBody(&bodyDef);
	rockBody->SetAngularDamping(1.0f);
	b2CircleShape rockShape;
	//�޸�Ϊ������Ĵ�С�ı�뾶
    rockShape.m_radius = mRock->radius;
    
    b2FixtureDef rockFixtureDef;
    rockFixtureDef.shape= &rockShape;
	rockFixtureDef.density=rockShape.m_radius*rockShape.m_radius*300;
	rockFixtureDef.restitution = 0.3f;//��������
	rockFixtureDef.friction=1.0f;

    rockBody->CreateFixture(&rockFixtureDef);

	mRock->setPTMRatio(RATIO);
	mRock->setB2Body(rockBody);
	mRock->setPosition(ccp( pt.x, pt.y));
	addChild(mRock);

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

	//��ӵ���
	addChild(fakeRock);
	//���scale������
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

	//���rock����
	addRock(endTime-beginTime,touchPoint,scale1);
}




long HelloWorld::getCurrentTime()    
{     
	struct cc_timeval tv;     
	CCTime::gettimeofdayCocos2d(&tv, NULL);  
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;     
}   



void HelloWorld::update(float dt){
	if(rockgrowing)
	{
		//mscale*=1.03;
		//mRock->setScale( mscale );
	}
	//�ж�����ɳ���ĻΪʤ��
	if(mbolloon->getB2Body()->GetPosition().y>(screenSize.height+20)/RATIO) 
	{
		stopGame();
	}
	mbolloon->getB2Body()->ApplyForceToCenter(b2Vec2(0.0f, 0.1f));

	world->Step(dt, 8, 3);

}

void HelloWorld::stopGame(){
    unscheduleUpdate();
	CCMessageBox("����þ���", "Congratulation !!");
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
