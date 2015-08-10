//
//  GameMapScene.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/5.
//
//

#include "GameMapScene.h"
#include "GameHomeScene.h"
#include "GameFightScene.h"
#include "GameShopScene.h"
#include "MapScrollHeadler.h"

bool GameMapScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("yinying.plist"));
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic((MusicPath("shopMusic.mp3")).c_str());
    
    
    MenuItem * houmItem = MenuItemImage::create(ImagePath("map_homeButton.png"),
                                                    ImagePath("map_homeButton.png"),
                                                    CC_CALLBACK_1(GameMapScene::homeButtonFuc, this));
    houmItem->setPosition(m_visibleOrigin.x + 60,
                    m_visibleOrigin.y + m_visibleSize.height - 60);
    MenuItem * shopItem = MenuItemImage::create(ImagePath("map_shopButton.png"),
                                                ImagePath("map_shopButton.png"),
                                                CC_CALLBACK_1(GameMapScene::shopButtonFuc, this));
    shopItem->setPosition(m_visibleOrigin.x + m_visibleSize.width - 60,
                          m_visibleOrigin.y + m_visibleSize.height - 60);
    m_leftItem = MenuItemImage::create(ImagePath("map_leftButton.png"),
                                                ImagePath("map_leftButton.png"),
                                                CC_CALLBACK_1(GameMapScene::leftButtonFuc, this));
    m_leftItem->setPosition(m_visibleOrigin.x + 60,
                          m_visibleOrigin.y +  60);
    m_rightItem = MenuItemImage::create(ImagePath("map_rightButton.png"),
                                                ImagePath("map_rightButton.png"),
                                                CC_CALLBACK_1(GameMapScene::rightButtonFuc, this));
    m_rightItem->setPosition(m_visibleOrigin.x + m_visibleSize.width - 60,
                          m_visibleOrigin.y + 60);
    
    Menu * buttonMenu = Menu::create(houmItem,
                                     shopItem,
                                     m_leftItem,
                                     m_rightItem, NULL);
    buttonMenu->setPosition(Point::ZERO);
    addChild(buttonMenu,2);
    
    
    int num = 3;
    m_scrollView = new GameHorizontalScrollHeadlerView(1136,640,1136,640,num);
    m_scrollView->setScrollControllerContentWidth(1136 * num);
    m_scrollView->setScrollControllerContentHeight(640);
    m_scrollView->setScrollUndulate(false);
    m_scrollView->setGetHeadlerTarget(this);
    m_scrollView->setScrollHorizontal(false);
    
    m_scrollView->initView();
    m_scrollView->autorelease();
    m_scrollView->setPosition(0,0);
    addChild(m_scrollView);
    
    
    moveToEndCall();
    
    
    return true;
}
GameScrollHeadler * GameMapScene::getHeadlerByIndex(int index,int viewTag)
{
    Vec2 v_p = Vec2(1136 * (index + 1) - 1136 * 0.5, 640 * 0.5);

    MapScrollHeadler * headler = new MapScrollHeadler(index);
    headler->autorelease();
    headler->setPosition(v_p);
    return headler;
}
void GameMapScene::moveToEndCall()
{
    if (m_scrollView->canMoveMinusView())
    {
        m_leftItem->setVisible(true);
    }else
    {
        m_leftItem->setVisible(false);
    }
    if (m_scrollView->canMoveAddView())
    {
        m_rightItem->setVisible(true);
    }else
    {
        m_rightItem->setVisible(false);
    }

}
void GameMapScene::homeButtonFuc(cocos2d::Ref *psender)
{
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Director::getInstance()->replaceScene(GameHomeScene::scene());
}
void GameMapScene::shopButtonFuc(cocos2d::Ref *psender)
{
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Director::getInstance()->replaceScene(GameShopScene::scene());
}
void GameMapScene::leftButtonFuc(cocos2d::Ref *psender)
{
//    log("left move");
    m_scrollView->moveMinusView();
}
void GameMapScene::rightButtonFuc(cocos2d::Ref *psender)
{
//    log("right move");
    m_scrollView->moveAddView();
}
