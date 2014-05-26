#ifndef __DATA_H__
#define __DATA_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "constant.h"
#include "LocalStorage/LocalStorage.h"

//必须使用这个cocos2d::extension命名空间来使用CCPhysicsSprite
USING_NS_CC_EXT;
USING_NS_CC;


class Data
{

public:
	static void DBinit();
	static void DBFree();
	static void DBSetItem( const char *key, const char *value);
	static const char* DBGetItem( const char *key );
	static void DBRemoveItem( const char *key );

protected:


};

#endif // __DATA_H__
