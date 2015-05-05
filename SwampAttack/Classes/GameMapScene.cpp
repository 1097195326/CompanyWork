//
//  GameMapScene.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/5.
//
//

#include "GameMapScene.h"

bool GameMapScene::init()
{
    if (!LayerColor::init())
    {
        return false;
    }
    Sprite * bgSprite = Sprite::create(ImagePath("shopBg.png"));
//    addChild(bgSprite);
//    bgSprite->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 0.5, visibleOrigin.y + visibleSize.height * 0.5));
    
//    bgSprite->setTextureRect(Rect(0, 0, 400, 500));
//    bgSprite->setPosition(Vec2( 0, 0));
//    bgSprite->setContentSize(Size(1000,600));
    
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->setSwallowTouches(true);
//    
//    listener->onTouchBegan = [](Touch* touch, Event* event){
//        GameMapScene * gameFightScene = static_cast<GameMapScene *>(event->getCurrentTarget());
//        gameFightScene->touchBegan(touch, event);
//        return true;
//    };
//    listener->onTouchMoved = [](Touch* touch, Event* event){
//        GameMapScene * gameFightScene = static_cast<GameMapScene *>(event->getCurrentTarget());
//        gameFightScene->touchMoved(touch, event);
//    };
//    listener->onTouchEnded = [](Touch* touch, Event* event){
//        GameMapScene * gameFightScene = static_cast<GameMapScene *>(event->getCurrentTarget());
//        gameFightScene->touchEnd(touch, event);
//    };
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
//    setContentSize(Size(200, 100));
//    setCameraMask(20,true);
//    ClippingNode::create();
    LayerColor * layerColor = LayerColor::create(Color4B(200, 0, 0, 200));
    layerColor->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 0.5, visibleOrigin.y + visibleSize.height * 0.5));
    addChild(layerColor);
    layerColor->setContentSize(Size(200,300));
    layerColor->addChild(bgSprite);
    
    Director::getInstance()->getNotificationNode();
    return true;
}
bool GameMapScene::touchBegan(Touch *touch, Event *event)
{
    log("touch");
    return true;
}
void GameMapScene::touchMoved(Touch *touch, Event *event)
{
    
}
void GameMapScene::touchEnd(Touch *touch, Event *event)
{
    
}