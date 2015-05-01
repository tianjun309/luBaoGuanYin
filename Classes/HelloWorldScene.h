#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "cocostudio\CocoStudio.h" 
#include "cocostudio\CCArmatureDataManager.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocostudio;

class HelloWorld : public cocos2d::Layer , public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    cocos2d::Label* temp;
	cocostudio::CCArmature* armature;

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);


	virtual void testEvent(cocostudio::CCArmature *armature, MovementEventType movementType, const std::string& movementID);
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
};

#endif // __HELLOWORLD_SCENE_H__
