//
//  ShopHealthShowLayer.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/29.
//
//

#include "ShopHealthShowLayer.h"
#include "GameSprite.h"
#include "GameUser.h"


shopHealthShowLayer::~shopHealthShowLayer()
{
    if(m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
shopHealthShowLayer::shopHealthShowLayer(Vec2 position)
{
    init();
    m_point = position;
    
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(shopHealthShowLayer::touchBegan, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(shopHealthShowLayer::touchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
    
    setSubject(_G_U);
    
    layerColor = LayerColor::create(Color4B(0, 0, 0, 0));
    addChild(layerColor);
    layerColor->runAction(FadeTo::create(0.3, 120));
    
    bg = Sprite::create(ImagePath("healthShowBg.png"));
    bg->setPosition(position);
    addChild(bg);
    
    Size bgSize = bg->getContentSize();
    
    Sprite * title = Sprite::create(ImagePath("healthPowerTitle.png"));
    title->setPosition(bgSize.width * 0.5, bgSize.height * 0.68);
    bg->addChild(title);
    Sprite * text = Sprite::create(ImagePath("healthShowText.png"));
    text->setPosition(bgSize.width * 0.5, bgSize.height * 0.5);
    bg->addChild(text);
    
    m_healthSprites.reserve(5);
    for (int i = 0; i < 5; ++i) {
        Sprite * xinBg = Sprite::create(ImagePath("shopXinBg.png"));
        Sprite * xin = Sprite::create(ImagePath("shopXinIcon.png"));
        
        Vec2 xinP = Vec2(bgSize.width * 0.3 + xinBg->getContentSize().width * 1.2 * i,
                         bgSize.height * 0.3);
        xinBg->setPosition(xinP);
        xin->setPosition(xinP);
        xinBg->setScale(1.5);
        xin->setScale(1.5);
        bg->addChild(xinBg);
        bg->addChild(xin);
        xin->setVisible(false);
        m_healthSprites.push_back(xin);
    }
    
    updateView();
    
    bg->setScale(0.001);
    bg->runAction(Spawn::create(MoveTo::create(0.3,Vec2(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                                                        m_visibleOrigin.y + m_visibleSize.height * 0.5)),
                                ScaleTo::create(0.3, 1),
                                NULL));
    
    schedule(CC_SCHEDULE_SELECTOR(shopHealthShowLayer::update), 1);
    
}
void shopHealthShowLayer::updateView()
{
    Size bgSize = bg->getContentSize();
    int userHealth = GameUser::getInstance()->getUserHealth();
    if (userHealth > 0)
    {
        for (int i = 0; i < 5; ++i)
        {
            if (i < userHealth)
            {
                m_healthSprites[i]->setVisible(true);
            }else
            {
                m_healthSprites[i]->setVisible(false);
            }
        }
    }else
    {
        
        
        GameSprite * button = new GameSprite(ImagePath("healthShowButton.png"));
        button->setPosition(bgSize.width * 0.5,
                            bgSize.height * 0.3);
        button->m_touchMeCall = CC_CALLBACK_2(shopHealthShowLayer::useToolToAddHealth, this);
        bg->addChild(button);
        Sprite * hpIcon = Sprite::create(ImagePath("hp1_icon.png"));
        hpIcon->setPosition(bgSize.width * 0.63,
                            bgSize.height * 0.3);
        bg->addChild(hpIcon);
        Label * buttonTex = Label::createWithTTF("added  1x",
                                                 "fonts/Arial Black.ttf",
                                                 40);
        buttonTex->enableOutline(Color4B(0, 0, 0, 255),4);
        buttonTex->setPosition(bgSize.width * 0.45,
                            bgSize.height * 0.3);
        bg->addChild(buttonTex);
    }
    m_timeLabel = Label::createWithTTF("",
                                       "fonts/Arial Black.ttf",
                                       30);
    m_timeLabel->setPosition(bgSize.width * 0.5, bgSize.height * 0.2);
    m_timeLabel->enableOutline(Color4B(0, 0, 0, 255),3);
    bg->addChild(m_timeLabel);
}
void shopHealthShowLayer::updateData()
{
    updateView();
}
void shopHealthShowLayer::update(float data)
{
    int userHealth = GameUser::getInstance()->getUserHealth();
    if (userHealth == 5)
    {
        return;
    }else
    {
        int time = _G_AddTime - _G_U->getTime();
//        log("shop time :%d",time);
        int fen = time / 60;
        int miao = time % 60;
        m_timeLabel->setString(StringUtils::format("%02d:%02d",fen,miao));
    }
}
void shopHealthShowLayer::setDelegateLayer(UserDelegateLayer * layer)
{
    m_delegateLayer = layer;
}
void shopHealthShowLayer::useToolToAddHealth(cocos2d::Touch *touch, cocos2d::Event *event)
{
//    Sprite * spr = (Sprite *)event->getCurrentTarget();
    //    log("touch item %d",spr->getTag());
    
    if (_G_U->useExpendProp())
    {
        _G_U->addHealthToFull();
        m_delegateLayer->updateUserData();
    }
}
bool shopHealthShowLayer::touchBegan(Touch *touch, Event *event)
{
    return true;
}
void shopHealthShowLayer::touchEnd(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Vec2 point = bg->convertToNodeSpace(touch->getLocation());
    Rect rect = Rect(0, 0, bg->getContentSize().width, bg->getContentSize().height);
    if (rect.containsPoint(point))
    {
        return;
    }
    
    layerColor->stopAllActions();
    bg->stopAllActions();
    layerColor->runAction(FadeTo::create(0.3, 0));
    bg->runAction(Sequence::create(Spawn::create(MoveTo::create(0.3,m_point),
                                                 ScaleTo::create(0.3, 0.001),
                                                 NULL),
                                   CallFunc::create(CC_CALLBACK_0(shopHealthShowLayer::actionEndCall, this)),
                                   NULL
                                   ));
}
void shopHealthShowLayer::actionEndCall()
{
    layerColor->stopAllActions();
    bg->stopAllActions();
    removeFromParentAndCleanup(true);
}