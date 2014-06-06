#include "EditScene.h"
#include <stdlib.h>
#include "AppMacros.h"
#include "MenuScene.h"

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
	//���治��b2world��ֻ��obstacle��bolloon�ľ��飬����¼�����������Ҫ��ʱ��ʹ��obstacle��bolloon��������������
	//���ƻ�ͼ�༭���档
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();



	// ���ӷ��ذ�ť
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

	//�Ϸ���һ������ͼƬ�˵������Σ�Բ�Σ�������
	//�ڶ�������ͼƬ�˵���������������ľͷ


	mRectangle_D = CCMenuItemImage::create("Rec_D.png",NULL,this,menu_selector(EditScene::rectangleSetting));
	mCircle_D = CCMenuItemImage::create("circle_D.png",NULL,this,menu_selector(EditScene::circleSetting));
	mTriangle_D = CCMenuItemImage::create("Tri_D.png",NULL,this,menu_selector(EditScene::triangleSetting));
	//Ĭ��ʹ�÷���
	mRectangle_D->setOpacity(255);
	mCircle_D->setOpacity(128); 
	mTriangle_D->setOpacity(128); 
	this->drawShape=RECTANGLE;


	CCMenu* menu = CCMenu::create(mRectangle_D,mCircle_D,mTriangle_D, NULL);
	menu->alignItemsHorizontallyWithPadding(80);

	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();
	menu->setPosition(ccp(screenSize.width/2, screenSize.height-30));


	this->addChild(menu, 1);

	//����һ��layer����Ϊchild�����а���3�����ʵ�menu����һ�ŵ�menu��������layer���޸ġ�
	// 'layer' is an autorelease object
	MenuLayer *menuLayer = MenuLayer::create();

	this->addChild(menuLayer,1,1);

	//������������2��slider�����������x��y�����scale���ο�GUI��slider����
	this->addSliders();

	return true;
}

void  EditScene::addSliders()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	m_pUiLayer = UILayer::create();
	this->addChild(m_pUiLayer);
	// Create the ���� slider
	m_pDisplayValueLabel_H = UILabel::create();
	m_pDisplayValueLabel_H->setText("Move the slider thumb");
	m_pDisplayValueLabel_H->setFontName("Marker Felt");
	m_pDisplayValueLabel_H->setFontSize(32);
	m_pDisplayValueLabel_H->setAnchorPoint(ccp(0.5f, -1));
	m_pDisplayValueLabel_H->setPosition(ccp(origin.x + visibleSize.width/2 ,origin.y + visibleSize.height*4/5+15));
	m_pUiLayer->addWidget(m_pDisplayValueLabel_H);


	MySlider* slider = MySlider::create();
	slider->setVertical(false);
	slider->setTouchEnabled(true);
	slider->loadBarTexture("sliderTrack.png");
	slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	slider->loadProgressBarTexture("sliderProgress.png");
	slider->setPosition(ccp(origin.x + visibleSize.width/2 ,origin.y + visibleSize.height*4/5));

	slider->addEventListenerSlider(this, sliderpercentchangedselector(EditScene::sliderEvent));
	m_pUiLayer->addWidget(slider);

	//��������slider 
	m_pDisplayValueLabel_V = UILabel::create();
	m_pDisplayValueLabel_V->setText("Move the slider thumb");
	m_pDisplayValueLabel_V->setFontName("Marker Felt");
	m_pDisplayValueLabel_V->setFontSize(32);
	m_pDisplayValueLabel_V->setAnchorPoint(ccp(0.5f, -1));
	m_pDisplayValueLabel_V->setRotation(-90);
	m_pDisplayValueLabel_V->setPosition(ccp(origin.x + visibleSize.width*1/8 +15 ,origin.y + visibleSize.height/2));
	m_pUiLayer->addWidget(m_pDisplayValueLabel_V);

	slider = MySlider::create();
	slider->setVertical(true);//����ǹؼ�
	slider->setTouchEnabled(true);
	slider->loadBarTexture("sliderTrack2.png");
	slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	slider->loadProgressBarTexture("sliderProgress2.png");
	slider->setPosition(ccp(origin.x + visibleSize.width*1/8 ,origin.y + visibleSize.height/2));

	slider->addEventListenerSlider(this, sliderpercentchangedselector(EditScene::sliderEvent2));
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
			m_pDisplayValueLabel_H->setText(CCString::createWithFormat("Percent %d", percent)->getCString());
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
			m_pDisplayValueLabel_V->setText(CCString::createWithFormat("Percent %d", percent)->getCString());
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

		//�޸�MenuLayer��ͼƬ��Ϊ���Ρ�
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
		//�޸�MenuLayer��ͼƬ��ΪԲ�Ρ�
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
		//�޸�MenuLayer��ͼƬ��Ϊ�����Ρ�
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
	//�ڴ��㴦������һ���Ѷ�����״�Ͳ��ʵ�sprite����update�а��շŴ�ϵ���Ŵ󡣲�������������
	return true;
}
void EditScene::ccTouchEnded(CCTouch* touch, CCEvent* event)
{


}

void EditScene::updateGame(float dt)
{

}

void EditScene::menuBackCallback(CCObject* pSender)
{
	CCScene *scene = MenuScene::scene();

	CCDirector::sharedDirector()->replaceScene(scene);  

}








bool MenuLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	//���ӵڶ���menu
	mMetal_R = CCMenuItemImage::create("Rec_D.png",NULL,this,menu_selector(MenuLayer::MetalSettingR));
	mGlass_R = CCMenuItemImage::create("Rec_D.png",NULL,this,menu_selector(MenuLayer::GlassSettingR));
	mWood_R = CCMenuItemImage::create("Rec_D.png",NULL,this,menu_selector(MenuLayer::WoodSettingR));

	//Ĭ��ʹ��metal ����
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

//����
void MenuLayer::MetalSettingR(CCObject* sender)
{
	if( this->mMetal_R->getOpacity() == 128 )
	{
		this->mMetal_R->setOpacity(255);
		this->mGlass_R->setOpacity(128);
		this->mWood_R->setOpacity(128);
		this->drawMaterial=METAL;

		//�ڶ������Ӳ���menu��


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

//Բ��

void MenuLayer::MetalSettingC(CCObject* sender)
{
	if( this->mMetal_C->getOpacity() == 128 )
	{
		this->mMetal_C->setOpacity(255);
		this->mGlass_C->setOpacity(128);
		this->mWood_C->setOpacity(128);
		this->drawMaterial=METAL;

		//�ڶ������Ӳ���menu��

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
//������

void MenuLayer::MetalSettingT(CCObject* sender)
{
	if(this-> mMetal_T->getOpacity() == 128 )
	{
		this->mMetal_T->setOpacity(255);
		this->mGlass_T->setOpacity(128);
		this->mWood_T->setOpacity(128);
		this->drawMaterial=METAL;

		//�ڶ������Ӳ���menu��

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

	//�ȶ���ѡ��
	mMetal_R->setOpacity(128);
	mGlass_R->setOpacity(128); 
	mWood_R->setOpacity(128); 
	//���ݵ�ǰ�����ж�
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

	mMetal_C = CCMenuItemImage::create("circle_D.png",NULL,this,menu_selector(MenuLayer::MetalSettingC));
	mGlass_C = CCMenuItemImage::create("circle_D.png",NULL,this,menu_selector(MenuLayer::GlassSettingC));
	mWood_C = CCMenuItemImage::create("circle_D.png",NULL,this,menu_selector(MenuLayer::WoodSettingC));

	//�ȶ���ѡ��
	mMetal_C->setOpacity(128);
	mGlass_C->setOpacity(128); 
	mWood_C->setOpacity(128); 
	//���ݵ�ǰ�����ж�
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

	mMetal_T = CCMenuItemImage::create("Tri_D.png",NULL,this,menu_selector(MenuLayer::MetalSettingT));
	mGlass_T = CCMenuItemImage::create("Tri_D.png",NULL,this,menu_selector(MenuLayer::GlassSettingT));
	mWood_T = CCMenuItemImage::create("Tri_D.png",NULL,this,menu_selector(MenuLayer::WoodSettingT));
	//�ȶ���ѡ��
	mMetal_T->setOpacity(128);
	mGlass_T->setOpacity(128); 
	mWood_T->setOpacity(128); 
	//���ݵ�ǰ�����ж�
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