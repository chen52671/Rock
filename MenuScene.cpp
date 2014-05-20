#include "MenuScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"
#include "GameScene.h"
using namespace cocos2d;



CCScene* MenuScene::scene()
{
	CCScene * scene = NULL;

		// 'scene' is an autorelease object
		scene = CCScene::create();


		// 'layer' is an autorelease object
		MenuScene *layer = MenuScene::create();


		// add layer as a child to scene
		scene->addChild(layer);


	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(MenuScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

	//增加一个开始游戏的按钮-BEGIN

    CCMenuItemImage *pStartGame = CCMenuItemImage::create(
                                        "StartGame1.png",
                                        "StartGame1.png",
                                        this,
                                        menu_selector(MenuScene::menuStartGame));
    
	pStartGame->setPosition(ccp(origin.x +visibleSize.width/2 ,
		origin.y +visibleSize.height/2));

    CCMenu* pStart = CCMenu::create(pStartGame, NULL);
    pStart->setPosition(CCPointZero);
    this->addChild(pStart, 1);

	//增加一个开始游戏的按钮_END


  
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Bolloon Rescue", "Arial", TITLE_FONT_SIZE);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "MenuScene" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    return true;

}
void MenuScene::menuStartGame(CCObject* pSender)
{
    CCScene * pScene =  GameScene::scene();
    if (pScene)
    {
		CCDirector::sharedDirector()->replaceScene(pScene);
        pScene->release();
    }
}

void MenuScene::menuCloseCallback(CCObject* pSender)
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
