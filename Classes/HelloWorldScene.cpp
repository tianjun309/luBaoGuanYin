#include "HelloWorldScene.h"
#include "cocostudio\CCArmatureDataManager.h"







Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	auto temp1 = Sprite::create("CyanSquare.png");
	temp1->setPosition(100,200);
	this->addChild(temp1,1);

	auto temp2 = Sprite::create("MagentaSquare.png");
	temp2->setPosition(300,200);
	this->addChild(temp2,10);

	auto temp3 = Sprite::create("YellowSquare.png");
	temp3->setPosition(300,600);
	this->addChild(temp3,20);

	std::string myname = UserDefault::getInstance()->getStringForKey("name","none");
	 temp = Label::create(myname,"宋体",20);
	
	temp->setPosition(300,400);
	this->addChild(temp,21);

	auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);

	listener1->onTouchBegan = [this](Touch* touch, Event* event){

		temp->setString("nice");

		  //获得触摸点坐标
    Point touchLocation = touch->getLocation();
    
    CCParticleSystemQuad* mParticle =  CCParticleSystemQuad::create("temp.plist");
    mParticle->setScale(0.3f);
    mParticle->setPosition(touchLocation);
    //如果不设置,粒子播放后内存不释放
    mParticle->setAutoRemoveOnFinish(true);
    this->addChild(mParticle,88);

		//   //获得当前注册过的监听sprite
  //      auto target = static_cast<Sprite*>(event->getCurrentTarget());
  //      //获得当前点-注册监听sprite之间的相对坐标
  //      Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		////获得当前sprite的大小
  //      Size s = target->getContentSize();
  //      //获得当前sprite坐标范围
		//Rect rect = Rect(0, 0, s.width, s.height);
		////检查当前点
  //      if (rect.containsPoint(locationInNode))
  //      {
		//	temp4->setString("sdflsjdflsdf");
  //          return true;
  //      }
        return false;
    };

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, temp1);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), temp2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), temp3);







	TableView* tableView = TableView::create(this, Size(60, 250));
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	tableView->setPosition(400,200);
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	this->addChild(tableView);
	tableView->reloadData();










	//从导出文件异步加载动画
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("test/Hero0.png","test/Hero0.plist","test/Hero.ExportJson");
	//根据动画名称创建动画精灵
	armature = CCArmature::create("Hero");
	armature->setPosition(200,200);
	armature->getAnimation()->play("run");
	armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(HelloWorld::testEvent));
	this->addChild(armature,10);
    return true;
}

void HelloWorld::testEvent(cocostudio::CCArmature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (movementType == COMPLETE)
    {
		if (movementID == "attack")
        {
            armature->getAnimation()->play("run");
            armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(HelloWorld::testEvent));
        }
    }

}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}



void HelloWorld::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
	UserDefault::getInstance()->setStringForKey("name","mytest " + Value((int)(cell->getIdx())).asString());
	temp->setString("mytest " + Value((int)(cell->getIdx())).asString());
	if(armature->getAnimation()->getCurrentMovementID() != "attack")
	{
		armature->getAnimation()->play("attack");
	}
	
}

cocos2d::Size HelloWorld::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	 return Size(60, 60);
}

cocos2d::extension::TableViewCell* HelloWorld::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	auto string = String::createWithFormat("%ld", idx);
	TableViewCell* cell = table->dequeueCell();

	if (!cell) {
        cell = new TableViewCell();
        cell->autorelease();
        auto sprite = Sprite::create("Icon.png");
        sprite->setAnchorPoint(Vec2::ZERO);
        sprite->setPosition(Vec2(0, 0));
        cell->addChild(sprite,1);

        auto label = Label::createWithSystemFont(string->getCString(), "Helvetica", 20.0);
        label->setPosition(Vec2::ZERO);
		label->setAnchorPoint(Vec2::ZERO);
        label->setTag(123);
        cell->addChild(label,2);
    }
    else
    {
        auto label = (Label*)cell->getChildByTag(123);
        label->setString(string->getCString());
    }

	return cell;
}

ssize_t HelloWorld::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
	return 10;
}
