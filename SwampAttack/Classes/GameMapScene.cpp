//
//  GameMapScene.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/5.
//
//

#include "GameMapScene.h"
#include "GameScrollView.h"
#include "GameVerticalScrollHeadlerView.h"
#include "GameFightScene.h"

bool GameMapScene::init()
{
    if (!LayerColor::init())
    {
        return false;
    }
    Sprite * bg = Sprite::create(ImagePath("shopBg.png"));
    bg->setPosition(visibleOrigin.x + visibleSize.width * 0.5, visibleOrigin.y + visibleSize.height * 0.5);
    addChild(bg);
    
    Sprite * bgSprite = Sprite::create(ImagePath("shopBg.png"));
    bgSprite->setPosition(visibleOrigin.x + visibleSize.width * 0.5, visibleOrigin.y + visibleSize.height * 0.5);
    
    MenuItem * buttonSprite = MenuItemImage::create("CloseNormal.png",
                                                    "CloseNormal.png",
                                                    CC_CALLBACK_1(GameMapScene::buttonTouch, this));
    buttonSprite->setPosition(visibleOrigin.x + visibleSize.width * 0.5,
                    visibleOrigin.y + visibleSize.height * 0.5);
    
    Menu * buttonMenu = Menu::create(buttonSprite, NULL);
    buttonMenu->setPosition(Point::ZERO);
    addChild(buttonMenu);
    
    
    
//    GameVerticalScrollHeadlerView * scrollView = new GameVerticalScrollHeadlerView(800,500,800,210,6);
//    scrollView->setGetHeadlerTarget(this);
//    scrollView->setScrollControllerContentWidth(800);
//    scrollView->setScrollControllerContentHeight(210 * 6);
//    
//    scrollView->autorelease();
//    addChild(scrollView);
//    
//    scrollView->setPosition(Vec2(100,100));
//    scrollView->addChild(bgSprite);
//    scrollView->addChildToScrollView(s1);
    
    

    
    
    return true;
}
void GameMapScene::buttonTouch(cocos2d::Ref *psender)
{
    Director::getInstance()->replaceScene(GameFightScene::scene());
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