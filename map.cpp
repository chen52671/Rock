#include "map.h"
#include "Box2D/Box2D.h"


void Map::addBackgrondBox()
{

}
void Map::addMap()
{


	  
	CCSize worldsize =CCDirector::sharedDirector()->getVisibleSize();
	CCSize groudsize =this->getContentSize();
    b2BodyDef bDef;
    bDef.type = b2_staticBody;
    bDef.position = b2Vec2(worldsize.width/2/RATIO, 0.0f);
    b2Body *groundBody = world->CreateBody(&bDef);
	 
	//µ×±ß
		b2FixtureDef groundFixtureDef;
	        b2Body* ground = NULL;
            b2BodyDef bd;
			ground = world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.Set(b2Vec2(-40.0f, groudsize.height/2/RATIO), b2Vec2(40.0f,groudsize.height/2/RATIO));
			groundFixtureDef.shape=&shape;
			groundFixtureDef.friction=0.5;
            ground->CreateFixture(&groundFixtureDef);
	//Ìí¼Ó×ó±ßÇ½±Ú
		b2FixtureDef wallFixtureDef;
	        b2Body* liftwall = NULL;
            b2BodyDef lwallBD;
			liftwall = world->CreateBody(&lwallBD);

			shape.Set(b2Vec2(0.0f, 0.0f), b2Vec2(0.0f, 10.0f));
			wallFixtureDef.shape=&shape;
			wallFixtureDef.friction=0.5;
            ground->CreateFixture(&wallFixtureDef);
	//Ìí¼ÓÓÒ±ßÇ½±Ú
	        b2Body* rightwall = NULL;
            b2BodyDef rwallBD;
			
			rightwall = world->CreateBody(&rwallBD);

			shape.Set(b2Vec2(worldsize.width/RATIO, 0.0f), b2Vec2(worldsize.width/RATIO, 10.0f));
			wallFixtureDef.shape=&shape;
			wallFixtureDef.friction=2;
            ground->CreateFixture(&wallFixtureDef);

			

    /*
    b2PolygonShape groundShape;
    groundShape.SetAsBox(groudsize.width/2/RATIO, groudsize.height/2/RATIO);
    b2FixtureDef groundFixtureDef;
    groundFixtureDef.shape = &groundShape;
    groundBody->CreateFixture(&groundFixtureDef);
    */

    this->setB2Body(groundBody);
    this->setPTMRatio(RATIO);



/*
	b2BodyDef bd;
	bd.position.Set(4.0f, 0.5f);
	b2Body* body = world->CreateBody(&bd);

	b2EdgeShape edge;

	edge.Set(b2Vec2(-10.0f, 0.0f), b2Vec2(10.0f, 0.0f));
	body->CreateFixture(&edge, 0.0f);

	this->setPTMRatio(RATIO);
	this->setB2Body(body);
	this->setPosition(ccp(4.0f, 0.5f));
*/
}

Map*  Map::creatAndInit(b2World *world)
{
	Map *_map = new Map();
	_map->world = world;


	CCTexture2D *textureRock = CCTextureCache::sharedTextureCache()->addImage("groundx.png");


	if (_map && _map->initWithTexture(textureRock))
	{
		_map->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(_map);
	}

	return _map;

}
