#include "EditScene.h"
#include <stdlib.h>
#include "AppMacros.h"
#include "MenuScene.h"

USING_NS_CC;

EditScene::EditScene():
	_Obstacle(NULL),
	selectedObstacle(NULL)
{

}
EditScene::~EditScene()
{
	if (_Obstacle)
	{
		_Obstacle->release();
		_Obstacle = NULL;
	}
}

CCScene* EditScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	EditScene *layer = EditScene::create();

	// add layer as a child to scene
	scene->addChild(layer);


	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool EditScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	_Obstacle= new CCArray;//初始化障碍物数组。
	//界面不加b2world，只有obstacle和bolloon的精灵，并记录精灵参数，需要的时候，使用obstacle和bolloon类来创建物理精灵
	//绘制绘图编辑界面。
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//开启触摸
	setTouchEnabled(true);

	//1 初始化物理世界，重力为0
	initWorld();
	//增加地面和墙壁
	addGround();
	// 增加返回按钮-稍后改为暂停
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(EditScene::menuBackCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
		origin.y + visibleSize.height - pCloseItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	//上方第一排增加图片菜单：矩形，圆形，三角形
	//第二排增加图片菜单：金属，玻璃，木头
	addMenu();



	//横竖方向增加2个slider。调节物体的x，y方向的scale。参考GUI的slider例子
	this->addSliders();



	//scheduleUpdate();
	this->schedule( schedule_selector(EditScene::updateGame) );


	return true;
}
void  EditScene::addMenu()
{

	mRectangle_D = CCMenuItemImage::create("Rec_E.png",NULL,this,menu_selector(EditScene::rectangleSetting));
	mCircle_D = CCMenuItemImage::create("circle_E.png",NULL,this,menu_selector(EditScene::circleSetting));
	mTriangle_D = CCMenuItemImage::create("Tri_E.png",NULL,this,menu_selector(EditScene::triangleSetting));
	//默认使用方形
	mRectangle_D->setOpacity(255);
	mCircle_D->setOpacity(128); 
	mTriangle_D->setOpacity(128); 
	this->drawShape=RECTANGLE;


	CCMenu* menu = CCMenu::create(mRectangle_D,mCircle_D,mTriangle_D, NULL);
	menu->alignItemsHorizontallyWithPadding(80);

	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();
	menu->setPosition(ccp(screenSize.width/2, screenSize.height-30));


	this->addChild(menu, 1);

	//增加一个layer，作为child，其中包括3个材质的menu，第一排的menu，触发该layer的修改。
	// 'layer' is an autorelease object
	menuLayer = MenuLayer::create();

	this->addChild(menuLayer,2,1);

}
void  EditScene::addSliders()
{
	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	origin = CCDirector::sharedDirector()->getVisibleOrigin();

	m_pUiLayer = UILayer::create();
	//把zorder设为100，这样滑块不会被物体阻挡。
	this->addChild(m_pUiLayer,100);
	// Create the 横向 slider

	MySlider* slider = MySlider::create();
	slider->setVertical(false);
	slider->setTouchEnabled(true);
	slider->loadBarTexture("sliderTrack.png");
	slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	slider->loadProgressBarTexture("sliderProgress.png");
	slider->setPosition(ccp(origin.x + visibleSize.width/2 ,origin.y + visibleSize.height*5/6));

	slider->addEventListenerSlider(this, sliderpercentchangedselector(EditScene::sliderEvent));
	m_pUiLayer->addWidget(slider);

	//增加纵向slider 1

	slider = MySlider::create();
	slider->setVertical(true);//这个是关键
	slider->setTouchEnabled(true);
	slider->loadBarTexture("sliderTrack2.png");
	slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	slider->loadProgressBarTexture("sliderProgress2.png");
	slider->setPosition(ccp(origin.x + 10 ,origin.y + visibleSize.height/2-10));

	slider->addEventListenerSlider(this, sliderpercentchangedselector(EditScene::sliderEvent2));
	m_pUiLayer->addWidget(slider);

	//增加纵向slider 2 控制旋转

	slider = MySlider::create();
	slider->setVertical(true);//这个是关键
	slider->setTouchEnabled(true);
	slider->loadBarTexture("sliderTrack2.png");
	slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	slider->loadProgressBarTexture("sliderProgress2.png");
	slider->setPosition(ccp(origin.x + visibleSize.width-10 ,origin.y + visibleSize.height/2-10));

	slider->addEventListenerSlider(this, sliderpercentchangedselector(EditScene::sliderEvent3));
	m_pUiLayer->addWidget(slider);

}

void EditScene::sliderEvent(CCObject *pSender, SliderEventType type)
{
	switch (type)
	{
	case SLIDER_PERCENTCHANGED:
		{
			MySlider* slider = dynamic_cast<MySlider*>(pSender);
			int percent = slider->getPercent();

			//被选择物体，设定其Xpercent。
			if(selectedObstacle!=NULL)
			{
				selectedObstacle->scale.x=percent;

				updateObstacleTexture(selectedObstacle);
			}

		}
		break;

	default:
		break;
	}
}

void EditScene::sliderEvent2(CCObject *pSender, SliderEventType type)
{
	switch (type)
	{
	case SLIDER_PERCENTCHANGED:
		{
			MySlider* slider = dynamic_cast<MySlider*>(pSender);
			int percent = slider->getPercent();

			//被选择物体，设定其Xpercent。
			if(selectedObstacle!=NULL)
			{
				selectedObstacle->scale.y=percent;

				updateObstacleTexture(selectedObstacle);
			}

		}
		break;

	default:
		break;
	}
}

void EditScene::sliderEvent3(CCObject *pSender, SliderEventType type)
{
	switch (type)
	{
	case SLIDER_PERCENTCHANGED:
		{
			MySlider* slider = dynamic_cast<MySlider*>(pSender);
			int percent = slider->getPercent();

			//被选择物体，设定旋转。
			if(selectedObstacle!=NULL)
			{
				selectedObstacle->obstacleAngle=percent*3.6;

				updateObstacleTexture(selectedObstacle);
			}

		}
		break;

	default:
		break;
	}
}

void EditScene::rectangleSetting(CCObject* sender)
{
	if( mRectangle_D->getOpacity() == 128 )
	{
		mRectangle_D->setOpacity(255);
		mCircle_D->setOpacity(128); 
		mTriangle_D->setOpacity(128); 
		this->drawShape=RECTANGLE;

		//修改MenuLayer的图片都为矩形。
		//MenuLayer*menuLayer = (MenuLayer*)this->getChildByTag(1);
		menuLayer->showRec();

	}

}

void EditScene::circleSetting(CCObject* sender)
{	
	if( mCircle_D->getOpacity() == 128 )
	{
		mRectangle_D->setOpacity(128);
		mCircle_D->setOpacity(255); 
		mTriangle_D->setOpacity(128); 
		this->drawShape=CIRLE;
		//修改MenuLayer的图片都为圆形。
		//MenuLayer*menuLayer = (MenuLayer*)this->getChildByTag(1);
		menuLayer->showCircle();
	}

}

void EditScene::triangleSetting(CCObject* sender)
{
	if( mTriangle_D->getOpacity() == 128 )
	{
		mRectangle_D->setOpacity(128);
		mCircle_D->setOpacity(128); 
		mTriangle_D->setOpacity(255); 
		this->drawShape=TRIANGLE;
		//修改MenuLayer的图片都为三角形。
		//MenuLayer*menuLayer = (MenuLayer*)this->getChildByTag(1);
		menuLayer->showTriangle();
	}

}

void EditScene::registerWithTouchDispatcher()
{
	// higher priority than dragging
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -10, true);
}
bool EditScene::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	//触点在一个正方形区域并且，不触碰已存在的物体时，才会进一步传递。
	CCPoint touchLocation = touch->getLocation();    
	CCPoint touchPoint = convertToNodeSpace( touchLocation );
	//只有下面一半区域可以添加物体，并且左边调节条处也不可以放置。
	//循环遍历数组中的所有物体，如果都没有触碰，才可以放置。
	//如果触碰到了某个物体，则设物体的selected属性为true
	obstacle* child;
	CCObject* pObject = NULL;

	//更新物理世界
	if(selectedObstacle!=NULL)
		updateObstaclePhysics(selectedObstacle);

	if(touchPoint.x>origin.x + 15 &&touchPoint.x<origin.x +visibleSize.width - 15 &&touchPoint.y<origin.y + visibleSize.height*1/2)
	{

		//然后设选中的物体为selected
		CCARRAY_FOREACH(_Obstacle, pObject)
		{
			child = (obstacle*)pObject;
			if(! child )
				break;
			if (child->containPoint(touchPoint)) 
			{
				//child->setSelected(true);
				selectedObstacle =child;
				return false;
			}
		}
		selectedObstacle=NULL;
		return true;
	}	
	else 
	{

		return false;
	}

}
void EditScene::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCPoint touchLocation = touch->getLocation();    
	CCPoint touchPoint = convertToNodeSpace( touchLocation );
	//在触摸点增加一个drawShape和MenuLayer：：drawMaterial材质的物体。

	obstacle* mObstacle =obstacle::createObstacle(drawShape,menuLayer->drawMaterial,touchPoint);

	//创建一个无重力的物理世界，并将物体放到其中。当点击test按键时，改变物理世界的属性。

	addObstacle(mObstacle);



}


void EditScene::initWorld(){
	world = new b2World(b2Vec2(0, -0.1));

}

void EditScene::addObstacle(obstacle* mObstacle)

{

	//统一配置
	b2BodyDef bodyDef;
	b2PolygonShape RecShape;
	b2CircleShape CircleShape;
	b2PolygonShape TriShape;

	b2FixtureDef obstacleFixtureDef;
	float SideLength;
	b2Vec2 vertices[3];
	//Body配置		

	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(mObstacle->obstaclePosition.x/RATIO,mObstacle->obstaclePosition.y/RATIO);
	bodyDef.allowSleep = true;

	//此处应该根据9种不同状况来配置物体信息。
	//fixture配置,创建3种形状
	switch(mObstacle->obstacleShape)
	{
	case RECTANGLE:
		RecShape.SetAsBox(mObstacle->ObstacleSize.width/2/RATIO*(mObstacle->scale.x/100),mObstacle->ObstacleSize.height/2/RATIO*(mObstacle->scale.y/100));
		obstacleFixtureDef.shape= &RecShape; //外形
		break;
	case CIRLE:
		CircleShape.m_radius = mObstacle->ObstacleSize.width/2/RATIO*(mObstacle->scale.x/100);
		obstacleFixtureDef.shape= &CircleShape; //外形
		break;
	case TRIANGLE: //锚点在底边中点

		SideLength = mObstacle->ObstacleSize.width*(mObstacle->scale.x/100);
		vertices[0].Set(-0.5f*SideLength/RATIO, -0.865f*0.5f*SideLength/RATIO);
		vertices[1].Set(0.5f*SideLength/RATIO, -0.865f*0.5f*SideLength/RATIO);
		vertices[2].Set(0.0f, 0.865f*0.5f*SideLength/RATIO);
		TriShape.Set(vertices, 3);
		obstacleFixtureDef.shape= &TriShape; //外形
		break;
	default:
		break;

	}


	//设置材质信息
	switch (mObstacle->obstacleMaterial)
	{
	case METAL:
		obstacleFixtureDef.density=8; //密度
		obstacleFixtureDef.restitution = 0.0f;//反弹特性
		obstacleFixtureDef.friction=0.3f; //摩擦系数
		break;
	case GLASS:
		obstacleFixtureDef.density=2.5; //密度
		obstacleFixtureDef.restitution = 0.0f;//反弹特性
		obstacleFixtureDef.friction=0.2f; //摩擦系数
		break;
	case WOOD:
		obstacleFixtureDef.density=8; //密度
		obstacleFixtureDef.restitution = 0.3f;//反弹特性
		obstacleFixtureDef.friction=0.5f; //摩擦系数
		break;
	default:
		break;
	}


	b2Body *  ObstacleBody= world->CreateBody(&bodyDef);

	mObstacle->oldFixture=ObstacleBody->CreateFixture(&obstacleFixtureDef);




	mObstacle->setPTMRatio(RATIO);
	mObstacle->setB2Body(ObstacleBody);
	mObstacle->setPosition(ccp( mObstacle->getobstaclePosition().x,  mObstacle->getobstaclePosition().y));


	//test the mass
	b2MassData massData;
	ObstacleBody->GetMassData(&massData);


	addChild(mObstacle);

	_Obstacle->addObject(mObstacle);
}

void EditScene::updateGame(float dt)
{
	//物理世界更新
	world->Step(dt, 8, 3);

	//	if(selectedObstacle!=NULL)
	//		updateObstacleTexture(selectedObstacle);



}

bool EditScene::updateObstacleTexture(obstacle* mObstacle)
{
	if (mObstacle->scale.x<0 ||mObstacle->scale.y<0) return false;
	//设置贴图大小
	mObstacle->setScaleX(mObstacle->scale.x/100);
	mObstacle->setScaleY(mObstacle->scale.y/100);
	if(mObstacle->obstacleAngle>0)
	{
		mObstacle->setRotation(mObstacle->obstacleAngle);
		mObstacle->obstacleAngle = -1;
	}
	return true;

}
bool EditScene::updateObstaclePhysics(obstacle* mObstacle)
{
	//改变物理世界大小

	b2Body* ObstacleBody= mObstacle->getB2Body();
	//为物体重新创建fixture
	//统一配置
	b2BodyDef bodyDef;
	b2PolygonShape RecShape;
	b2CircleShape CircleShape;
	b2PolygonShape TriShape;

	b2FixtureDef obstacleFixtureDef;
	float SideLength;
	b2Vec2 vertices[3];
	//fixture配置,创建3种形状
	switch(mObstacle->obstacleShape)
	{
	case RECTANGLE:
		RecShape.SetAsBox(mObstacle->ObstacleSize.width/2/RATIO*(mObstacle->scale.x/100),mObstacle->ObstacleSize.height/2/RATIO*(mObstacle->scale.y/100));
		obstacleFixtureDef.shape= &RecShape; //外形
		break;
	case CIRLE:
		CircleShape.m_radius = mObstacle->ObstacleSize.width/2/RATIO*(mObstacle->scale.x/100);
		obstacleFixtureDef.shape= &CircleShape; //外形
		break;
	case TRIANGLE: //锚点在底边中点

		SideLength = mObstacle->ObstacleSize.width*(mObstacle->scale.x/100);
		vertices[0].Set(-0.5f*SideLength/RATIO, -0.865f*0.5f*SideLength/RATIO);
		vertices[1].Set(0.5f*SideLength/RATIO, -0.865f*0.5f*SideLength/RATIO);
		vertices[2].Set(0.0f, 0.865f*0.5f*SideLength/RATIO);
		TriShape.Set(vertices, 3);
		obstacleFixtureDef.shape= &TriShape; //外形
		break;
	default:
		break;

	}


	//设置材质信息
	switch (mObstacle->obstacleMaterial)
	{
	case METAL:
		obstacleFixtureDef.density=8; //密度
		obstacleFixtureDef.restitution = 0.0f;//反弹特性
		obstacleFixtureDef.friction=0.3f; //摩擦系数
		break;
	case GLASS:
		obstacleFixtureDef.density=2.5; //密度
		obstacleFixtureDef.restitution = 0.0f;//反弹特性
		obstacleFixtureDef.friction=0.2f; //摩擦系数
		break;
	case WOOD:
		obstacleFixtureDef.density=8; //密度
		obstacleFixtureDef.restitution = 0.3f;//反弹特性
		obstacleFixtureDef.friction=0.5f; //摩擦系数
		break;
	default:
		break;
	}
	//应该把原来的fixture删掉才可以——待修改。
	//设一个oldFixture 指针来保存原有的fixture，然后删除，新建一个fixture，并设为oldFixture
	if (mObstacle->oldFixture != NULL)
		ObstacleBody->DestroyFixture(mObstacle->oldFixture);


	mObstacle->oldFixture = ObstacleBody->CreateFixture(&obstacleFixtureDef);
	//mObstacle->setRotation(mObstacle->obstacleAngle);
	return true;
}

void EditScene::menuBackCallback(CCObject* pSender)
{
	// 测试
	CCMenuItemFont* itemRestart = CCMenuItemFont::create("Test", this, menu_selector(EditScene::onTest));
	//itemRestart->setFontSize(0.5*itemRestart->fontSize());

	// 保存
	CCMenuItemFont* itemNext = CCMenuItemFont::create("Sava", this, menu_selector(EditScene::onSave));
	//menu动画

	//继续编辑
	CCMenuItemFont* itemCancel = CCMenuItemFont::create("Back to Edit", this, menu_selector(EditScene::onEdit));
	// 返回主菜单 Item
	CCMenuItemFont* itemBack = CCMenuItemFont::create("Back to main menu", this, menu_selector(EditScene::onQuit));
	//itemBack->setFontSize(0.5*itemBack->fontSize());

	//创建menu
	CCMenu* menu = CCMenu::create(itemRestart,itemNext,itemCancel,itemBack,NULL);
	//竖向排列
	menu->alignItemsVerticallyWithPadding(40);

	addChild(menu,0,7);

	CCSize screenSize = CCDirector::sharedDirector()->getVisibleSize();

	menu->setPosition(ccp(screenSize.width/2, screenSize.height/2));



}


void EditScene::onEdit(CCObject* sender)
{
	SetSleepingAllowed(true);
	world->SetGravity(b2Vec2(0, -0.1));
	removeChildByTag(7);
}
void EditScene::onQuit(CCObject* sender)
{
	//
	CCScene *scene = MenuScene::scene();

	CCDirector::sharedDirector()->replaceScene(scene);  
}
void EditScene::onTest(CCObject* sender)
{
	SetSleepingAllowed(false);
	world->SetGravity(b2Vec2(0, -10));
	removeChildByTag(7);
}
void EditScene::onSave(CCObject* sender)
{

}
void EditScene::addGround()
{
	CCSize worldsize =CCDirector::sharedDirector()->getVisibleSize();

	b2BodyDef bDef;
	//底边
	b2FixtureDef groundFixtureDef;
	b2Body* ground = NULL;
	b2BodyDef bd;
	ground = world->CreateBody(&bd);

	b2EdgeShape shape;
	shape.Set(b2Vec2(-40.0f, 3.0f), b2Vec2(40.0f,3.0f));//地面高度待修改
	groundFixtureDef.shape=&shape;
	groundFixtureDef.friction=0.5;
	ground->CreateFixture(&groundFixtureDef);
	//添加左边墙壁
	b2FixtureDef wallFixtureDef;
	b2Body* liftwall = NULL;
	b2BodyDef lwallBD;
	liftwall = world->CreateBody(&lwallBD);

	shape.Set(b2Vec2(0.0f, 0.0f), b2Vec2(0.0f, 20.0f));
	wallFixtureDef.shape=&shape;
	wallFixtureDef.friction=0.5;
	ground->CreateFixture(&wallFixtureDef);
	//添加右边墙壁
	b2Body* rightwall = NULL;
	b2BodyDef rwallBD;

	rightwall = world->CreateBody(&rwallBD);

	shape.Set(b2Vec2(worldsize.width/RATIO, 0.0f), b2Vec2(worldsize.width/RATIO, 20.0f));
	wallFixtureDef.shape=&shape;
	wallFixtureDef.friction=2;
	ground->CreateFixture(&wallFixtureDef);


}

void EditScene::SetSleepingAllowed(bool allowed)
{
		obstacle* child;
	CCObject* pObject = NULL;



		//然后设选中的物体为selected
		CCARRAY_FOREACH(_Obstacle, pObject)
		{
			child = (obstacle*)pObject;
			if(! child )
				break;
			child->getB2Body()->SetSleepingAllowed(allowed);

		}

}












bool MenuLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	//增加第二排menu
	mMetal_R = CCMenuItemImage::create("MetalRectangle.png",NULL,this,menu_selector(MenuLayer::MetalSettingR));
	mGlass_R = CCMenuItemImage::create("GlassRectangle.png",NULL,this,menu_selector(MenuLayer::GlassSettingR));
	mWood_R = CCMenuItemImage::create("WoodRectangle.png",NULL,this,menu_selector(MenuLayer::WoodSettingR));
	mMetal_R->setScale(0.5);
	mGlass_R->setScale(0.5);
	mWood_R->setScale(0.5);

	//默认使用metal 矩形
	mMetal_R->setOpacity(255);
	mGlass_R->setOpacity(128); 
	mWood_R->setOpacity(128); 
	this->drawMaterial=METAL;


	CCMenu* menu = CCMenu::create(mMetal_R,mGlass_R,mWood_R, NULL);
	menu->alignItemsHorizontallyWithPadding(80);

	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();
	menu->setPosition(ccp(screenSize.width/2, screenSize.height-100));


	this->addChild(menu, 1,0);



	return true;
}



//矩形
void MenuLayer::MetalSettingR(CCObject* sender)
{
	if( this->mMetal_R->getOpacity() == 128 )
	{
		this->mMetal_R->setOpacity(255);
		this->mGlass_R->setOpacity(128);
		this->mWood_R->setOpacity(128);
		this->drawMaterial=METAL;

		//第二排增加材质menu，


	}

}

void MenuLayer::GlassSettingR(CCObject* sender)
{	
	if( this->mGlass_R->getOpacity() == 128 )
	{
		this->mMetal_R->setOpacity(128);
		this->mGlass_R->setOpacity(255);
		this->mWood_R->setOpacity(128);
		this->drawMaterial=GLASS;
	}

}

void MenuLayer::WoodSettingR(CCObject* sender)
{
	if(this-> mWood_R->getOpacity() == 128 )
	{
		this->mMetal_R->setOpacity(128);
		this->mGlass_R->setOpacity(128);
		this->mWood_R->setOpacity(255);
		this->drawMaterial=WOOD;
	}

}

//圆形

void MenuLayer::MetalSettingC(CCObject* sender)
{
	if( this->mMetal_C->getOpacity() == 128 )
	{
		this->mMetal_C->setOpacity(255);
		this->mGlass_C->setOpacity(128);
		this->mWood_C->setOpacity(128);
		this->drawMaterial=METAL;

		//第二排增加材质menu，

	}

}

void MenuLayer::GlassSettingC(CCObject* sender)
{	
	if(this-> mGlass_C->getOpacity() == 128 )
	{
		this->mMetal_C->setOpacity(128);
		this->mGlass_C->setOpacity(255);
		this->mWood_C->setOpacity(128);
		this->drawMaterial=GLASS;
	}

}

void MenuLayer::WoodSettingC(CCObject* sender)
{
	if(this-> mWood_C->getOpacity() == 128 )
	{
		this->mMetal_C->setOpacity(128);
		this->mGlass_C->setOpacity(128);
		this->mWood_C->setOpacity(255);
		this->drawMaterial=WOOD;
	}

}
//三角形

void MenuLayer::MetalSettingT(CCObject* sender)
{
	if(this-> mMetal_T->getOpacity() == 128 )
	{
		this->mMetal_T->setOpacity(255);
		this->mGlass_T->setOpacity(128);
		this->mWood_T->setOpacity(128);
		this->drawMaterial=METAL;

		//第二排增加材质menu，

	}

}

void MenuLayer::GlassSettingT(CCObject* sender)
{	
	if( this->mGlass_T->getOpacity() == 128 )
	{
		this->mMetal_T->setOpacity(128);
		this->mGlass_T->setOpacity(255);
		this->mWood_T->setOpacity(128);
		this->drawMaterial=GLASS;
	}

}

void MenuLayer::WoodSettingT(CCObject* sender)
{
	if(this-> mWood_T->getOpacity() == 128 )
	{
		this->mMetal_T->setOpacity(128);
		this->mGlass_T->setOpacity(128);
		this->mWood_T->setOpacity(255);
		this->drawMaterial=WOOD;
	}

}


void MenuLayer::showRec()
{
	this->removeChildByTag(0);



	mMetal_R = CCMenuItemImage::create("MetalRectangle.png",NULL,this,menu_selector(MenuLayer::MetalSettingR));
	mGlass_R = CCMenuItemImage::create("GlassRectangle.png",NULL,this,menu_selector(MenuLayer::GlassSettingR));
	mWood_R = CCMenuItemImage::create("WoodRectangle.png",NULL,this,menu_selector(MenuLayer::WoodSettingR));
	mMetal_R->setScale(0.5);
	mGlass_R->setScale(0.5);
	mWood_R->setScale(0.5);

	//先都不选中
	mMetal_R->setOpacity(128);
	mGlass_R->setOpacity(128); 
	mWood_R->setOpacity(128); 
	//根据当前材料判断
	switch (this->drawMaterial)
	{
	case METAL:
		mMetal_R->setOpacity(255);
		break;
	case GLASS:
		mGlass_R->setOpacity(255); 
		break;
	case WOOD:
		mWood_R->setOpacity(255); 
		break;
	default:
		break;
	}
	CCMenu* menu = CCMenu::create(this->mMetal_R,this->mGlass_R,this->mWood_R, NULL);
	menu->alignItemsHorizontallyWithPadding(80);

	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();
	menu->setPosition(ccp(screenSize.width/2, screenSize.height-100));


	this->addChild(menu, 1,0);

}
void MenuLayer::showCircle()
{

	this->removeChildByTag(0);

	mMetal_C = CCMenuItemImage::create("MetalCircle.png",NULL,this,menu_selector(MenuLayer::MetalSettingC));
	mGlass_C = CCMenuItemImage::create("GlassCircle.png",NULL,this,menu_selector(MenuLayer::GlassSettingC));
	mWood_C = CCMenuItemImage::create("WoodCircle.png",NULL,this,menu_selector(MenuLayer::WoodSettingC));

	mMetal_C->setScale(0.5);
	mGlass_C->setScale(0.5);
	mWood_C->setScale(0.5);

	//先都不选中
	mMetal_C->setOpacity(128);
	mGlass_C->setOpacity(128); 
	mWood_C->setOpacity(128); 
	//根据当前材料判断
	switch (this->drawMaterial)
	{
	case METAL:
		mMetal_C->setOpacity(255);
		break;
	case GLASS:
		mGlass_C->setOpacity(255); 
		break;
	case WOOD:
		mWood_C->setOpacity(255); 
		break;
	default:
		break;
	}
	CCMenu* menu = CCMenu::create(this->mMetal_C,this->mGlass_C,this->mWood_C, NULL);
	menu->alignItemsHorizontallyWithPadding(80);

	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();
	menu->setPosition(ccp(screenSize.width/2, screenSize.height-100));


	this->addChild(menu, 1,0);
}
void MenuLayer::showTriangle()
{
	this->removeChildByTag(0);

	mMetal_T = CCMenuItemImage::create("MetalTriangle.png",NULL,this,menu_selector(MenuLayer::MetalSettingT));
	mGlass_T = CCMenuItemImage::create("GlassTriangle.png",NULL,this,menu_selector(MenuLayer::GlassSettingT));
	mWood_T = CCMenuItemImage::create("WoodTriangle.png",NULL,this,menu_selector(MenuLayer::WoodSettingT));
	mMetal_T->setScale(0.5);
	mGlass_T->setScale(0.5);
	mWood_T->setScale(0.5);


	//先都不选中
	mMetal_T->setOpacity(128);
	mGlass_T->setOpacity(128); 
	mWood_T->setOpacity(128); 
	//根据当前材料判断
	switch (this->drawMaterial)
	{
	case METAL:
		mMetal_T->setOpacity(255);
		break;
	case GLASS:
		mGlass_T->setOpacity(255); 
		break;
	case WOOD:
		mWood_T->setOpacity(255); 
		break;
	default:
		break;
	}
	CCMenu* menu = CCMenu::create(this->mMetal_T,this->mGlass_T,this->mWood_T, NULL);
	menu->alignItemsHorizontallyWithPadding(80);

	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();
	menu->setPosition(ccp(screenSize.width/2, screenSize.height-100));


	this->addChild(menu, 1,0);
}
