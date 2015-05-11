//
//  GameShopScene.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#include "GameShopScene.h"
#include "GameVerticalScrollHeadlerView.h"
#include "ShopSelectMeumView.h"


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
    scrollBg->setPosition(bg2->getTextureRect().size.width * 0.5, bg2->getTextureRect().size.height * 0.368);
    bg2->addChild(scrollBg);
    
    ShopSelectMenuView * menuView = new ShopSelectMenuView(4);
    menuView->autorelease();
    setSubject(menuView);
    menuView->setNormalSprite("shopItemNormal");
    menuView->setSelectSprite("shopItemSelect");
    menuView->setIconSprite("shopItemIcon");
    menuView->checkIndex();
    menuView->setPosition(bg2->getTextureRect().size.width * 0.5, bg2->getTextureRect().size.height * 0.8);
    bg2->addChild(menuView);
    
    
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
void GameShopScene::updateData()
{
    log("shop scene update data");
}
GameScrollHeadler * GameShopScene::getHeadlerByIndex(int index)
{
    
}