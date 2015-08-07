//
//  GameShowDiscLayer.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/10.
//
//

#include "GameShowDiscLayer.h"
#include "GameShopScene.h"


GameShowDiscLayer::~GameShowDiscLayer()
{
    if(m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
GameShowDiscLayer::GameShowDiscLayer(std::string name,std::string disc,Vec2 position,bool isUnlock)
{
    init();
    m_point = position;
    
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(GameShowDiscLayer::touchBegan, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(GameShowDiscLayer::touchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
    
    
    layerColor = LayerColor::create(Color4B(0, 0, 0, 0));
    addChild(layerColor);
    layerColor->runAction(FadeTo::create(0.5, 200));
    
    bg = Sprite::create(ImagePath("shop_show_discbg.png"));
    bg->setPosition(position);
    addChild(bg);
    
    
    std::string iconName = StringUtils::format("%s_icon.png",name.c_str());
    std::string textName = StringUtils::format("%s_name.png",name.c_str());
    
    Sprite * iconSpr = Sprite::create(ImagePath(iconName));
    Sprite * nameSpr = Sprite::create(ImagePath(textName));
    Label  * discLabel = Label::createWithTTF(disc, "fonts/mimi.ttf", 30);
    discLabel->setColor(Color3B(0, 0, 0));
    
    MenuItemImage * gotoShopButton = MenuItemImage::create(ImagePath("overScene_toShop.png"),
                                                           ImagePath("overScene_toShop.png"),
                                                           CC_CALLBACK_1( GameShowDiscLayer::gotoShop, this));
    
    Size bgSize = bg->getContentSize();
    iconSpr->setPosition(bgSize.width * 0.21, bgSize.height * 0.75);
    nameSpr->setPosition(bgSize.width * 0.68, bgSize.height * 0.58);
    discLabel->setPosition(bgSize.width * 0.5, bgSize.height * 0.37);
    gotoShopButton->setPosition(bgSize.width * 0.5, bgSize.height * 0.15);
    
    Menu * gotoShopMenu = Menu::create(gotoShopButton, NULL);
    gotoShopMenu->setPosition(Vec2::ZERO);
    
    bg->addChild(iconSpr);
    bg->addChild(nameSpr);
    bg->addChild(discLabel);
    
    if (isUnlock)
    {
        bg->addChild(gotoShopMenu);
    }
    
    
    bg->setScale(0.001);
    bg->runAction(Spawn::create(MoveTo::create(0.5,Vec2(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                                               m_visibleOrigin.y + m_visibleSize.height * 0.5)),
                                ScaleTo::create(0.5, 1),
                                NULL));
    
    
}

bool GameShowDiscLayer::touchBegan(Touch *touch, Event *event)
{
    return true;
}
void GameShowDiscLayer::touchEnd(cocos2d::Touch *touch, cocos2d::Event *event)
{
    layerColor->stopAllActions();
    bg->stopAllActions();
    layerColor->runAction(FadeTo::create(0.5, 0));
    bg->runAction(Sequence::create(Spawn::create(MoveTo::create(0.5,m_point),
                                                ScaleTo::create(0.5, 0.001),
                                                NULL),
                                   CallFunc::create(CC_CALLBACK_0(GameShowDiscLayer::actionEndCall, this)),
                                   NULL
                                   ));
}
void GameShowDiscLayer::actionEndCall()
{
    layerColor->stopAllActions();
    bg->stopAllActions();
    removeFromParentAndCleanup(true);
}
void GameShowDiscLayer::gotoShop(cocos2d::Ref *pSender)
{
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Director::getInstance()->replaceScene(GameShopScene::scene());
}