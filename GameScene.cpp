#include "GameScene.h"
#include <stdlib.h>
#include "AppMacros.h"
#include "GameOverScene.h"
#include "MenuScene.h"
USING_NS_CC;

CCScene* GameScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	GameScene *layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	mscale = 0.01f;
	rockMassTotal=0;
	rockPercent=100.00;
	rockMassTotal=0.0;
	rockgrowing=false;
	screenSize = CCDirector::sharedDirector()->getVisibleSize();
	//开启触摸
	setTouchEnabled(true);
	//1 初始化物理世界
	initWorld();
	//2 加载地图。
	addMap();
	//把气球放在地面上
	addBolloon(ccp(200.0,60.0));
	//把障碍放上
	addObstacle(0,ccp(140.0,80.0),b2_pi*0.5,b2Vec2(0.2f, 0.2f),0);
	addObstacle(1,ccp(200.0,100.0),0.0,b2Vec2(0.4f, 0.2f),1);
	addObstacle(0,ccp(260.0,80.0),b2_pi*0.5,b2Vec2(0.2f, 0.2f),2);
	mRock =new Rock();
	//
	addRockPercent();
	
	//scheduleUpdate();
	this->schedule( schedule_selector(GameScene::updateGame) );

	return true;
}



void GameScene::initWorld(){
	world = new b2World(b2Vec2(0, -10));

}
void  GameScene::addMap()
{
	 mMap=Map::creatAndInit(world);
	 mMap->addMap();


	 addChild(mMap);
}
void GameScene::addBolloon(CCPoint pt)
{
	mbolloon=Bolloon::createBolloon(pt);
	CCSize size = mbolloon->getContentSize();//2倍半径
	mbolloon->radius = (size.width*0.5*0.2)/RATIO;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.allowSleep = false;
	b2Body *  BolloonBody= world->CreateBody(&bodyDef);
	
	b2CircleShape BolloonShape;
	//修改为根据球的大小改变半径
    BolloonShape.m_radius = mbolloon->radius;
    
    b2FixtureDef rockFixtureDef;
    rockFixtureDef.shape= &BolloonShape;
	rockFixtureDef.density=0.1;
	rockFixtureDef.restitution = 0.3f;//反弹特性
	rockFixtureDef.friction=1.0f;



    BolloonBody->CreateFixture(&rockFixtureDef);
	mbolloon->setPTMRatio(RATIO);
	mbolloon->setB2Body(BolloonBody);
	mbolloon->setPosition(ccp( pt.x, pt.y));
	
	//test the mass
	b2MassData massData;
    BolloonBody->GetMassData(&massData);
	mbolloon->weight=massData.mass;
	//施加重力1.1倍的向上的力
	BolloonBody->ApplyForceToCenter(b2Vec2(0.0f, mbolloon->weight*11));
	addChild(mbolloon);

}
void GameScene::addObstacle(int type,CCPoint pt,float angle,const b2Vec2& scale,int key)
{
	obstacle* mObstacle =obstacle::createObstacle(type,pt,scale);

	CCSize size = mObstacle->getContentSize();//2倍半径
	

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
	rockFixtureDef.density=3;
	rockFixtureDef.restitution = 0.0f;//反弹特性
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

void GameScene::addRock(float dt,CCPoint pt,float scale)
{
		mRock =Rock::createRock(0,pt,scale);
		//设置小球物理世界半径
	CCSize size = mRock->getContentSize();//2倍半径
	mRock->setRadius(size.width/2/RATIO*scale);
	//将小球放进层

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(pt.x/RATIO, pt.y/RATIO);
	bodyDef.allowSleep = true;
	b2Body *  rockBody= world->CreateBody(&bodyDef);
	rockBody->SetAngularDamping(1.0f);
	b2CircleShape rockShape;
	//修改为根据球的大小改变半径
    rockShape.m_radius = mRock->radius;
    
    b2FixtureDef rockFixtureDef;
    rockFixtureDef.shape= &rockShape;
	rockFixtureDef.density=10;
	rockFixtureDef.restitution = 0.3f;//反弹特性
	rockFixtureDef.friction=1.0f;

    rockBody->CreateFixture(&rockFixtureDef);

	mRock->setPTMRatio(RATIO);
	mRock->setB2Body(rockBody);
	mRock->setPosition(ccp( pt.x, pt.y));

	addChild(mRock);
	//计算石头重量
		//test the mass
	b2MassData massData;
    rockBody->GetMassData(&massData);
	mRock->weight=massData.mass;
	rockMassTotal+=mRock->weight;
	rockPercent=100-rockMassTotal;
}
void GameScene::addRockPercent()
{
	char str[25];
	sprintf(str, "%d",(int)rockPercent);
    rockPercentLabel = CCLabelTTF::create(str, "Arial", TITLE_FONT_SIZE);
    
    // position the label on the center of the screen
	rockPercentLabel->setPosition(ccp(screenSize.width*0.8,screenSize.height*0.9));

    // add the label as a child to this layer
    this->addChild(rockPercentLabel, 1);
}

void GameScene::registerWithTouchDispatcher()
{
	// higher priority than dragging
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -10, true);
}
bool GameScene::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if(rockPercent<=0) return true;
	CCPoint touchLocation = touch->getLocation();    

	touchPoint = convertToNodeSpace( touchLocation );
	beginTime=getCurrentTime();
	//画一个最小的fakeRock
	//在之后每一帧，rock放大一点点
	//直到ccTouchEnded，停止放大，然后绑定一个box2d对象。
	fakeRock = CCSprite::create("rock.png");
	fakeRock->setPosition(ccp( touchPoint.x, touchPoint.y));
	fakeRock->setScale(mscale);

	//添加到层
	addChild(fakeRock);
	//添加scale动作。
	actionTo = CCScaleTo::create(5.0f, 0.15f);	
	fakeRock->runAction( actionTo);
	rockgrowing=true;
	return true;
}
void GameScene::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	rockgrowing=false;
	fakeRock->stopAction(actionTo);
	float scale1=fakeRock->getScale();
	//删除fakerock
	removeChild(fakeRock);
	//获取松开时间
	endTime=getCurrentTime();

	//添加rock精灵
	if(rockPercent>0)
	{
		addRock(endTime-beginTime,touchPoint,scale1);
	}
	else stopGame();
	
}




long GameScene::getCurrentTime()    
{     
	struct cc_timeval tv;     
	CCTime::gettimeofdayCocos2d(&tv, NULL);  
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;     
}   



void GameScene::updateGame(float dt){
	if(rockPercent<=0)
	{
		
	}


	mbolloon->getB2Body()->ApplyForceToCenter(b2Vec2(0.0f, mbolloon->weight*11));
	//更新剩余石头百分比
		if(rockPercentLabel)
	{
	char str[25];
	sprintf(str, "%d",(int)rockPercent);
	rockPercentLabel->setString(str);
	world->Step(dt, 8, 3);
	}
	//判断气球飞出屏幕为胜利
	if(mbolloon->getB2Body()->GetPosition().y>(screenSize.height+20)/RATIO) 
	{
		stopGame();
	}

}

void GameScene::stopGame(){
   //销毁b2body，和对应的sprite
	 CCSprite *s;
	    for (b2Body *b = world->GetBodyList(); b!=NULL; b=b->GetNext()) {
        if (b->GetPosition().x<-3) {
            s = (CCSprite*)b->GetUserData();
            if (s!=NULL) {
                s->removeFromParent();
            }
            
            world->DestroyBody(b);
        }
    }

		 unscheduleUpdate();

		 showEndMenu();
}

void GameScene::showEndMenu(){
	// 重新开始 Item
    CCMenuItemFont* itemRestart = CCMenuItemFont::create("Restart", this, menu_selector(GameScene::onRestart));
	//itemRestart->setFontSize(0.5*itemRestart->fontSize());

	// 下一关 Item
    CCMenuItemFont* itemNext = CCMenuItemFont::create("Next Stage", this, menu_selector(GameScene::onNext));
	//menu动画
	 CCActionInterval* color_action = CCTintBy::create(0.5f, 0, -255, -255);
    CCActionInterval* color_back = color_action->reverse();
    CCSequence* seq = CCSequence::create(color_action, color_back, NULL);
    itemNext->runAction(CCRepeatForever::create(seq));

	// 返回主菜单 Item
    CCMenuItemFont* itemBack = CCMenuItemFont::create("Back", this, menu_selector(GameScene::onQuit));
	//itemBack->setFontSize(0.5*itemBack->fontSize());

	//创建menu
	CCMenu* menu = CCMenu::create(itemRestart,itemNext,itemBack,NULL);
	//横向排列
	menu->alignItemsVertically();

	addChild(menu);
    menu->setPosition(ccp(screenSize.width/2, screenSize.height/2));

}

void GameScene::onQuit(CCObject* sender)
{
	    CCScene *scene = MenuScene::scene();

		CCDirector::sharedDirector()->pushScene(scene);  
}
void GameScene::onRestart(CCObject* sender)
{
	    CCScene *scene = GameScene::scene();

    CCDirector::sharedDirector()->pushScene(scene);  
}
void GameScene::onNext(CCObject* sender)
{

}
void GameScene::menuCloseCallback(CCObject* pSender)
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

