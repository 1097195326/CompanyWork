//
//  GameMapScene.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/5.
//
//

#include "GameMapScene.h"
#include "GameScrollView.h"


bool GameMapScene::init()
{
    if (!LayerColor::init())
    {
        return false;
    }
    Sprite * bg = Sprite::create("HelloWorld.png");
    bg->setPosition(visibleOrigin.x + visibleSize.width * 0.5, visibleOrigin.y + visibleSize.height * 0.5);
    addChild(bg);
    
    Sprite * bgSprite = Sprite::create(ImagePath("shopBg.png"));
    bgSprite->setPosition(visibleOrigin.x + visibleSize.width * 0.5, visibleOrigin.y + visibleSize.height * 0.5);
    Sprite * s1 = Sprite::create("CloseNormal.png");
    
    GameScrollView * scrollView = new GameScrollView(300,200);
    scrollView->setScrollControllerContentWidth(1136);
    scrollView->setScrollControllerContentHeight(640);
    scrollView->autorelease();
    addChild(scrollView);
    
    scrollView->setPosition(Vec2(200,200));
    scrollView->addChildToScrollView(bgSprite);
    scrollView->addChildToScrollView(s1);
    
    

    
    
    return true;
}
bool GameMapScene::touchBegan(Touch *touch, Event *event)
{
//    log("touch");
    return true;
}
void GameMapScene::touchMoved(Touch *touch, Event *event)
{
    
}
void GameMapScene::touchEnd(Touch *touch, Event *event)
{
    
}