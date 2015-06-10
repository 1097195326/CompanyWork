//
//  GameShowLevelupLayer.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/10.
//
//

#include "GameShowLevelupLayer.h"
#include "BaseUtil.h"

GameShowLevelupLayer::~GameShowLevelupLayer()
{
    if(m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
GameShowLevelupLayer::GameShowLevelupLayer(std::string name)
{
    init();
    setAnchorPoint(Vec2(0.5, 0.5));
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(GameShowLevelupLayer::touchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
    
    Sprite * texiao = Sprite::create();
    addChild(texiao,1);
    texiao->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5 + 25,
                        m_visibleOrigin.y + m_visibleSize.height * 0.5 - 15);
    texiao->setScale(2.8);
    ActionInterval * ac = BaseUtil::makeAnimateWithSprite("levelup_flash", 4);
    texiao->runAction(RepeatForever::create(ac));
    
    Sprite * bg = Sprite::create(ImagePath("shop_levelup_bg.png"));
    bg->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                        m_visibleOrigin.y + m_visibleSize.height * 0.5);
    addChild(bg,1);
    
    std::string iconName = StringUtils::format("%s_icon.png",name.c_str());
    std::string textName = StringUtils::format("%s_name.png",name.c_str());
    
    Sprite * iconSpr = Sprite::create(ImagePath(iconName));
    Sprite * nameSpr = Sprite::create(ImagePath(textName));
    Sprite * levelupLabel = Sprite::create(ImagePath("shop_levelup_label.png"));
    
    Size bgSize = bg->getContentSize();
    iconSpr->setPosition(bgSize.width * 0.5,bgSize.height * 0.43);
    nameSpr->setPosition(bgSize.width * 0.5,bgSize.height * 0.63);
    levelupLabel->setPosition(bgSize.width * 0.5,bgSize.height * 0.23);
    
    iconSpr->setScale(1.2);
    bg->addChild(iconSpr);
    bg->addChild(nameSpr);
    bg->addChild(levelupLabel);
    
    
    setScale(0.1);
    runAction(Sequence::create(ScaleTo::create(0.3, 1),
                               CallFuncN::create(CC_CALLBACK_1(GameShowLevelupLayer::addBackLayer, this)),
                               DelayTime::create(2),
                               ScaleTo::create(0.3, 0.1),
                               CallFuncN::create(CC_CALLBACK_1(GameShowLevelupLayer::timeIsEnd, this)), NULL));
    
}
void GameShowLevelupLayer::addBackLayer(cocos2d::Node *pSender)
{
    LayerColor * layerColor = LayerColor::create(Color4B(0, 0, 0, 0));
    addChild(layerColor);
    layerColor->runAction(Sequence::create(FadeTo::create(0.3, 150),
                                           DelayTime::create(1.4),
                                           FadeTo::create(0.3, 0),
                                           NULL) );
}
void GameShowLevelupLayer::timeIsEnd(Node * pSender)
{
    pSender->stopAllActions();
    pSender->removeFromParentAndCleanup(true);
}
bool GameShowLevelupLayer::touchBegan(Touch *touch, Event *event)
{
    return true;
}