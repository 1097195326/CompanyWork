//
//  GameShowDiscLayer.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/10.
//
//

#include "GameShowDiscLayer.h"


GameShowDiscLayer::~GameShowDiscLayer()
{
    if(m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
GameShowDiscLayer::GameShowDiscLayer()
{
    init();
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(GameShowDiscLayer::touchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
    
    Sprite * bg = Sprite::create(ImagePath("pauseScene_bg.png"));
    bg->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                    m_visibleOrigin.y + m_visibleSize.height * 0.5);
    addChild(bg);
    
    
//    MenuItemImage * continueButton = MenuItemImage::create(ImagePath("pauseScene_continue.png"),
//                                                           ImagePath("pauseScene_continue.png"),
//                                                           CC_CALLBACK_1( GamePauseScene::continueGame, this));
//    continueButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.55,
//                                m_visibleOrigin.y + m_visibleSize.height * 0.35);
//    
//    Menu * buttonMenu = Menu::create(gotoMapButton,restartButton,continueButton, NULL);
//    buttonMenu->setPosition(Point::ZERO);
//    addChild(buttonMenu,200);
    
}

bool GameShowDiscLayer::touchBegan(Touch *touch, Event *event)
{
    return true;
}