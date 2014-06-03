#include "EditScene.h"
#include <stdlib.h>
#include "AppMacros.h"

USING_NS_CC;

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
	//界面不加b2world，只有obstacle和bolloon的精灵，并记录精灵参数，需要的时候，使用obstacle和bolloon类来创建物理精灵
	//绘制绘图编辑界面。
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();



	// 增加返回按钮
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(EditScene::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
		origin.y + pCloseItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	//上方第一排增加图片菜单：矩形，圆形，三角形
	//第二排增加图片菜单：金属，玻璃，木头


	mRectangle_D = CCMenuItemImage::create("Rec_D.png",NULL,this,menu_selector(EditScene::rectangleSetting));
	mCircle_D = CCMenuItemImage::create("circle_D.png",NULL,this,menu_selector(EditScene::circleSetting));
	mTriangle_D = CCMenuItemImage::create("Tri_D.png",NULL,this,menu_selector(EditScene::triangleSetting));
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
	MenuLayer *menuLayer = MenuLayer::create();
	this->addChild(menuLayer);


	return true;
}



void EditScene::rectangleSetting(CCObject* sender)
{
	if( mRectangle_D->getOpacity() == 128 )
	{
		mRectangle_D->setOpacity(255);
		mCircle_D->setOpacity(128); 
		mTriangle_D->setOpacity(128); 
		this->drawShape=RECTANGLE;

		//第二排增加材质menu，

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
	}
	
}


void EditScene::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif

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
	mMetal = CCMenuItemImage::create("Rec_D.png",NULL,this,menu_selector(MenuLayer::MetalSetting));
	mGlass = CCMenuItemImage::create("circle_D.png",NULL,this,menu_selector(MenuLayer::GlassSetting));
	mWood = CCMenuItemImage::create("Tri_D.png",NULL,this,menu_selector(MenuLayer::WoodSetting));
	//默认使用metal
	mMetal->setOpacity(255);
	mGlass->setOpacity(128); 
	mWood->setOpacity(128); 
	this->drawMaterial=METAL;


	CCMenu* menu = CCMenu::create(mMetal,mGlass,mWood, NULL);
	menu->alignItemsHorizontallyWithPadding(80);

	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();
	menu->setPosition(ccp(screenSize.width/2, screenSize.height-100));


	this->addChild(menu, 1);

	return true;
}


void MenuLayer::MetalSetting(CCObject* sender)
{
	if( mMetal->getOpacity() == 128 )
	{
		mMetal->setOpacity(255);
		mGlass->setOpacity(128); 
		mWood->setOpacity(128); 
		this->drawMaterial=METAL;

		//第二排增加材质menu，

	}
	
}

void MenuLayer::GlassSetting(CCObject* sender)
{	
	if( mGlass->getOpacity() == 128 )
	{
		mMetal->setOpacity(128);
		mGlass->setOpacity(255); 
		mWood->setOpacity(128); 
		this->drawMaterial=GLASS;
	}
	
}

void MenuLayer::WoodSetting(CCObject* sender)
{
	if( mWood->getOpacity() == 128 )
	{
		mMetal->setOpacity(128);
		mGlass->setOpacity(128); 
		mWood->setOpacity(255); 
		this->drawMaterial=WOOD;
	}
	
}