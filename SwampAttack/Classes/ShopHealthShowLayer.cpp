//
//  ShopHealthShowLayer.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/29.
//
//

#include "ShopHealthShowLayer.h"
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
    layerColor->runAction(FadeTo::create(0.3, 200));
    
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
//        Sprite * xin = Sprite::create(ImagePath("shopXinIcon.png"));
        
        ProgressBar * xin = new ProgressBar("shopXinIcon.png","shopXinBg.png");
        xin->autorelease();
        xin->setBarRight();
        
        Vec2 xinP = Vec2(bgSize.width * 0.3 + xinBg->getContentSize().width * 1.2 * i,
                         bgSize.height * 0.3);
//        xinBg->setPosition(xinP);
        xin->setPosition(xinP);
//        xinBg->setScale(1.5);
        xin->setScale(1.5);
//        bg->addChild(xinBg);
        bg->addChild(xin);
//        xin->setVisible(false);
        m_healthSprites.push_back(xin);
    }
    m_timeLabel = Label::createWithTTF("",
                                       "fonts/Arial Black.ttf",
                                       30);
    m_timeLabel->setPosition(bgSize.width * 0.5, bgSize.height * 0.2);
    m_timeLabel->enableOutline(Color4B(0, 0, 0, 255),3);
    bg->addChild(m_timeLabel);
    
    
    m_button = new GameSprite(ImagePath("healthShowButton.png"));
    m_button->autorelease();
    m_button->setPosition(bgSize.width * 0.5,
                        bgSize.height * 0.32);
    m_button->m_touchMeCall = CC_CALLBACK_2(shopHealthShowLayer::useToolToAddHealth, this);
    bg->addChild(m_button);
    
    Size buttonSize = m_button->getContentSize();
    
    Sprite * hpIcon = Sprite::create(ImagePath("hp1_icon.png"));
    hpIcon->setPosition(buttonSize.width * 0.85,
                        buttonSize.height * 0.5);
    m_button->addChild(hpIcon);
    hpIcon->setScale(0.75);
    Label * buttonTex = Label::createWithTTF(StringUtils::format("added %d x",
                                                                 _G_U->getExpendPropNum()),
                                             "fonts/Arial Black.ttf",
                                             35);
    buttonTex->enableOutline(Color4B(0, 0, 0, 255),4);
    buttonTex->setAdditionalKerning(-5);
    buttonTex->setPosition(buttonSize.width * 0.4,
                           buttonSize.height * 0.5);
    m_button->addChild(buttonTex);
    
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
            m_healthSprites[i]->setVisible(true);
            
            if (i < (userHealth - 1)/ 2)
            {
                m_healthSprites[i]->updatePercent(100);
            }else if (i == (userHealth - 1)/ 2)
            {
                if ((userHealth) % 2)
                {
                    m_healthSprites[i]->updatePercent(50);
                }else
                {
                    m_healthSprites[i]->updatePercent(100);
                }
            }else
            {
                m_healthSprites[i]->updatePercent(0);
            }
        }
        m_button->setVisible(false);
        m_button->setCanTouch(false);
    }else
    {
        for (int i = 0; i < 5; ++i)
        {
            m_healthSprites[i]->setVisible(false);
        }
        m_button->setVisible(true);
        m_button->setCanTouch(true);
    }
    
}
void shopHealthShowLayer::updateData()
{
    updateView();
}
void shopHealthShowLayer::update(float data)
{
    int userHealth = GameUser::getInstance()->getUserHealth();
    if (userHealth == FullHealth)
    {
        m_timeLabel->setVisible(false);
        unschedule(CC_SCHEDULE_SELECTOR(shopHealthShowLayer::update));
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
        closeView();
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
    
    closeView();
}
void shopHealthShowLayer::actionEndCall()
{
    layerColor->stopAllActions();
    bg->stopAllActions();
    removeFromParentAndCleanup(true);
}
void shopHealthShowLayer::closeView()
{
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