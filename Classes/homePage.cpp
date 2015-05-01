#include "homePage.h"



Scene* homePage::createScene()
{
    auto scene = Scene::create();
    
    auto layer = homePage::create();

    scene->addChild(layer);

    return scene;
}

bool homePage::init()
{
	mytest();
	return true;
}

void homePage::mytest()
{
	
	auto lumian = Sprite::create("bg_sky_down.jpg");
	lumian->setPosition(239,184);
	this->addChild(lumian,1);

	auto sky = Sprite::create("bg_sky.jpg");
	sky->setPosition(239,584);
	this->addChild(sky,1);

	
}