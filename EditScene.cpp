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

	this->addChild(menuLayer,1,1);

	//横竖方向增加2个slider。调节物体的x，y方向的scale。

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

		//修改MenuLayer的图片都为矩形。
		MenuLayer*menuLayer = (MenuLayer*)this->getChildByTag(1);
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
		MenuLayer*menuLayer = (MenuLayer*)this->getChildByTag(1);
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
		MenuLayer*menuLayer = (MenuLayer*)this->getChildByTag(1);
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

	return true;
}
void EditScene::ccTouchEnded(CCTouch* touch, CCEvent* event)
{


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
	mMetal_R = CCMenuItemImage::create("Rec_D.png",NULL,this,menu_selector(MenuLayer::MetalSettingR));
	mGlass_R = CCMenuItemImage::create("Rec_D.png",NULL,this,menu_selector(MenuLayer::GlassSettingR));
	mWood_R = CCMenuItemImage::create("Rec_D.png",NULL,this,menu_selector(MenuLayer::WoodSettingR));
	
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

	mMetal_R = CCMenuItemImage::create("Rec_D.png",NULL,this,menu_selector(MenuLayer::MetalSettingR));
	mGlass_R = CCMenuItemImage::create("Rec_D.png",NULL,this,menu_selector(MenuLayer::GlassSettingR));
	mWood_R = CCMenuItemImage::create("Rec_D.png",NULL,this,menu_selector(MenuLayer::WoodSettingR));

	CCMenu* menu = CCMenu::create(this->mMetal_R,this->mGlass_R,this->mWood_R, NULL);
	menu->alignItemsHorizontallyWithPadding(80);

	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();
	menu->setPosition(ccp(screenSize.width/2, screenSize.height-100));


	this->addChild(menu, 1,0);

}
void MenuLayer::showCircle()
{

	this->removeChildByTag(0);

	mMetal_C = CCMenuItemImage::create("circle_D.png",NULL,this,menu_selector(MenuLayer::MetalSettingC));
	mGlass_C = CCMenuItemImage::create("circle_D.png",NULL,this,menu_selector(MenuLayer::GlassSettingC));
	mWood_C = CCMenuItemImage::create("circle_D.png",NULL,this,menu_selector(MenuLayer::WoodSettingC));
	
	CCMenu* menu = CCMenu::create(this->mMetal_C,this->mGlass_C,this->mWood_C, NULL);
	menu->alignItemsHorizontallyWithPadding(80);

	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();
	menu->setPosition(ccp(screenSize.width/2, screenSize.height-100));


	this->addChild(menu, 1,0);
}
void MenuLayer::showTriangle()
{
	this->removeChildByTag(0);

	mMetal_T = CCMenuItemImage::create("Tri_D.png",NULL,this,menu_selector(MenuLayer::MetalSettingT));
	mGlass_T = CCMenuItemImage::create("Tri_D.png",NULL,this,menu_selector(MenuLayer::GlassSettingT));
	mWood_T = CCMenuItemImage::create("Tri_D.png",NULL,this,menu_selector(MenuLayer::WoodSettingT));
	CCMenu* menu = CCMenu::create(this->mMetal_T,this->mGlass_T,this->mWood_T, NULL);
	menu->alignItemsHorizontallyWithPadding(80);

	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();
	menu->setPosition(ccp(screenSize.width/2, screenSize.height-100));


	this->addChild(menu, 1,0);
}