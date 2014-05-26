#include "data.h"


void Data::DBinit()
{
 std::string strFilePath = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
    strFilePath += "/chen.sqlite";
	localStorageInit(strFilePath.c_str());
	

}

void Data::DBFree()
{
	localStorageFree();
}
void Data::DBSetItem( const char *key, const char *value)
{
	localStorageSetItem(key,value);
}
const char*  Data::DBGetItem( const char *key )
{
	return localStorageGetItem( key );
}
void Data::DBRemoveItem( const char *key )
{
	localStorageRemoveItem(key );
}
