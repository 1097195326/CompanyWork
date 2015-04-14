//
//  GameFightScene.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "GameFightScene.h"
#include "EnemySprite.h"
#include "cocostudio/CocoStudio.h"

#include "CCCsvHelper.h"
#include "GameLoading.h"
#include "GameDirector.h"



using namespace cocostudio;

bool GameFightScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    GameLoading::loadFrames();
    
    Sprite * bgSprite = Sprite::create(ImagePath("bg.png"));
    addChild(bgSprite);
    bgSprite->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 0.5, visibleOrigin.y + visibleSize.height * 0.5));
    
    Sprite * test = Sprite::create(ImagePath("xuenei.png"));
    addChild(test);
    test->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 0.5, visibleOrigin.y + visibleSize.height * 0.5));
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        if (rect.containsPoint(locationInNode))
        {
            target->setOpacity(180);
            return true;
        }
        return false;
    };
    listener->onTouchMoved = [](Touch* touch, Event* event){
        
    };
    listener->onTouchEnded = [](Touch* touch, Event* event){
        
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, test);
    
    GameDirector * gameDirector = GameDirector::getInstance();
    gameDirector->setGameLayer(this);
    addChild(gameDirector);
    
    return true;
}

