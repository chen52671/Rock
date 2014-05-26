#ifndef __MenuScene_H__
#define __MenuScene_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

class MenuScene : public cocos2d::CCLayer
{
public:


	// Here's a difference. Method 'init' in cocos2d-x returns bool, 
    // instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	virtual void menuCloseCallback(cocos2d::CCObject* pSender);

	virtual void menuEasyMode(cocos2d::CCObject* pSender);
	virtual void menuLaunchMode(cocos2d::CCObject* pSender);
	virtual void menuMapEdit(cocos2d::CCObject* pSender);
	virtual void menuSetting(cocos2d::CCObject* pSender);
	
	// implement the "static node()" method manually
	CREATE_FUNC(MenuScene);


    



};

#endif  // __MenuScene_H__