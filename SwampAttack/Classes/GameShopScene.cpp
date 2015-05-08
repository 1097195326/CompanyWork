//
//  GameShopScene.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#include "GameShopScene.h"
#include "GameVerticalScrollHeadlerView.h"


bool GameShopScene::init()
{
    if (!LayerColor::init())
    {
        return false;
    }
    Sprite * bg = Sprite::create(ImagePath("shopBg.png"));
    bg->setPosition(visibleOrigin.x + visibleSize.width * 0.5, visibleOrigin.y + visibleSize.height * 0.5);
    addChild(bg);
    
    Sprite * bg2 = Sprite::create(ImagePath("shopBg2.png"));
    bg2->setPosition(visibleOrigin.x + visibleSize.width * 0.5, visibleOrigin.y + visibleSize.height * 0.5);
    addChild(bg2);
    Sprite * scrollBg = Sprite::create(ImagePath("shopScrollBg.png"));
    scrollBg->setPosition(bg2->getTextureRect().size.width * 0.5, bg2->getTextureRect().size.height * 0.4);
    bg2->addChild(scrollBg);
    
//    GameVerticalScrollHeadlerView * scrollView = new GameVerticalScrollHeadlerView(800,500,800,210,6);
//    
//    scrollView->setScrollControllerContentWidth(800);
//    scrollView->setScrollControllerContentHeight(210 * 6);
//    
//    scrollView->autorelease();
//    addChild(scrollView);
//    
//    scrollView->setPosition(Vec2(100,100));
//    scrollView->addChild(bgSprite);
    
    
    
    
    
    return true;
}
