#ifndef __homePage_H__
#define __homePage_H__

#include "cocos2d.h"


USING_NS_CC;


class homePage: public cocos2d::Layer
{
	public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
	virtual void mytest();
	 CREATE_FUNC(homePage);
};
#endif 