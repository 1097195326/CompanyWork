//
//  UserDelegatLayer.cpp
//  SwampAttack
//
//  Created by 张洪星 on 15/7/5.
//
//

#include "UserDelegatLayer.h"
#include "GameUser.h"

#include "ShopGoldShowLayer.h"
#include "ShopExpendShowLayer.h"
#include "ShopHealthShowLayer.h"



UserDelegateLayer::UserDelegateLayer()
{
    Sprite * upBg = Sprite::create(ImagePath("shopUpBg.png"));
    upBg->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                      m_visibleOrigin.y + m_visibleSize.height - upBg->getContentSize().height * 0.5);
    addChild(upBg,1);
    m_healthSprites.reserve(5);
    for (int i = 0; i < 5; ++i) {
        Sprite * xinBg = Sprite::create(ImagePath("shopXinBg.png"));
//        Sprite * xin = Sprite::create(ImagePath("shopXinIcon.png"));
        
        ProgressBar * xin = new ProgressBar("shopXinIcon.png","shopXinBg.png");
        xin->autorelease();
        xin->setBarRight();
        
        Vec2 xinP = Vec2(m_visibleOrigin.x + m_visibleSize.width * 0.15 +
                         xinBg->getContentSize().width * 0.8 * i,
                         m_visibleOrigin.y + m_visibleSize.height * 0.935);
//        xinBg->setPosition(xinP);
        xin->setPosition(xinP);
//        addChild(xinBg,3);
        addChild(xin,3);
//        xin->updatePercent(100);
//        xin->setVisible(true);
        m_healthSprites.push_back(xin);
    }
    
    
    m_goldLabel = Label::createWithTTF(StringUtils::format("%d",_G_U->getUserGold()),
                                       "fonts/Arial Black.ttf",
                                       27);
    m_goldLabel->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.57,
                             m_visibleOrigin.y + m_visibleSize.height * 0.93);
    m_goldLabel->enableOutline(Color4B(0, 0, 0, 255),3);
    m_goldLabel->setAdditionalKerning(-3);
    addChild(m_goldLabel,3);
    Sprite * jinbiIcon = Sprite::create(ImagePath("jinbi_icon.png"));
    jinbiIcon->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.47,
                           m_visibleOrigin.y + m_visibleSize.height * 0.934);
    addChild(jinbiIcon,3);
    
    m_expendPropLabel = Label::createWithTTF(StringUtils::format("%d",_G_U->getExpendPropNum()),
                                             "fonts/Arial Black.ttf",
                                             27);
    m_expendPropLabel->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.78,
                                   m_visibleOrigin.y + m_visibleSize.height * 0.93);
    m_expendPropLabel->enableOutline(Color4B(0, 0, 0, 255),3);
    m_expendPropLabel->setAdditionalKerning(-3);
    addChild(m_expendPropLabel,3);
    Sprite * hpIcon = Sprite::create(ImagePath("hp1_icon.png"));
    hpIcon->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.73,
                        m_visibleOrigin.y + m_visibleSize.height * 0.935);
    hpIcon->setScale(0.5);
    addChild(hpIcon,3);
    
    MenuItemImage * healthPlusButton = MenuItemImage::create(ImagePath("shop_plusIcon.png"),
                                                             ImagePath("shop_plusIcon.png"),
                                                             CC_CALLBACK_1(UserDelegateLayer::healthPlusFunc, this));
    healthPlusButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.39,
                                  m_visibleOrigin.y +  m_visibleSize.height * 0.935);
    
    MenuItemImage * goldPlusButton = MenuItemImage::create(ImagePath("shop_plusIcon.png"),
                                                           ImagePath("shop_plusIcon.png"),
                                                           CC_CALLBACK_1(UserDelegateLayer::goldPlusFunc, this));
    goldPlusButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.66,
                                m_visibleOrigin.y +  m_visibleSize.height * 0.935);
    MenuItemImage * expendPlusButton = MenuItemImage::create(ImagePath("shop_plusIcon.png"),
                                                             ImagePath("shop_plusIcon.png"),
                                                             CC_CALLBACK_1(UserDelegateLayer::expendPlusFunc, this));
    expendPlusButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.85,
                                  m_visibleOrigin.y +  m_visibleSize.height * 0.935);
    
    
    Menu * buttonMenu = Menu::create(healthPlusButton,
                                     goldPlusButton,
                                     expendPlusButton,
                                      NULL);
    buttonMenu->setPosition(Point::ZERO);
    addChild(buttonMenu,2);
    
    updateData();
    _G_U->attach(this);
//    setSubject(_G_U);
    
}
UserDelegateLayer::~UserDelegateLayer()
{
    m_healthSprites.clear();
    _G_U->detach(this);
}
void UserDelegateLayer::updateData()
{
//    log("user delegate layer update data");
    int userHealth = _G_U->getUserHealth();
    log("userHealth:%d",userHealth);
    
    for (int i = 0; i < 5; ++i)
    {
        if (userHealth > 0 && i < (userHealth - 1)/ 2)
        {
            m_healthSprites[i]->updatePercent(100);
        }else if (userHealth > 0 && i == (userHealth - 1)/ 2)
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
    
    m_goldLabel->setString(StringUtils::format("%d",_G_U->getUserGold()));
    m_expendPropLabel->setString(StringUtils::format("%d",_G_U->getExpendPropNum()));
    
}
void UserDelegateLayer::updateUserData()
{
//    m_goldLabel->setString(StringUtils::format("%d",_G_U->getUserGold()));
//    m_expendPropLabel->setString(StringUtils::format("%d",_G_U->getExpendPropNum()));

    updateData();
}

void UserDelegateLayer::healthPlusFunc(cocos2d::Ref *pSender)
{
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Node * pNode = (Node *)pSender;
    shopHealthShowLayer * layer = new shopHealthShowLayer(pNode->getPosition());
    layer->autorelease();
    layer->setDelegateLayer(this);
    addChild(layer,4);
}
void UserDelegateLayer::goldPlusFunc(cocos2d::Ref *pSender)
{
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Node * pNode = (Node *)pSender;
    ShopGoldShowLayer * layer = new ShopGoldShowLayer(pNode->getPosition());
    layer->autorelease();
    layer->setDelegateLayer(this);
    addChild(layer,4);
    
}
void UserDelegateLayer::expendPlusFunc(cocos2d::Ref *pSender)
{
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Node * pNode = (Node *)pSender;
    ShopExpendShowLayer * layer = new ShopExpendShowLayer(pNode->getPosition());
    layer->autorelease();
    layer->setDelegateLayer(this);
    addChild(layer,4);
}