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
GameShowDiscLayer::GameShowDiscLayer(std::string name,std::string disc,Vec2 position)
{
    init();
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(GameShowDiscLayer::touchBegan, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(GameShowDiscLayer::touchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
    
    
    LayerColor * layerColor = LayerColor::create(Color4B(0, 0, 0, 0));
    addChild(layerColor);
    layerColor->runAction(FadeTo::create(0.3, 120));
    
    Sprite * bg = Sprite::create(ImagePath("shop_show_discbg.png"));
    bg->setPosition(position);
    addChild(bg);
    bg->setScale(0.1);
    bg->runAction(Spawn::create(MoveTo::create(0.3,Vec2(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                                               m_visibleOrigin.y + m_visibleSize.height * 0.5)),
                                ScaleTo::create(0.3, 1),
                                NULL));
    
    
}

bool GameShowDiscLayer::touchBegan(Touch *touch, Event *event)
{
    return true;
}
void GameShowDiscLayer::touchEnd(cocos2d::Touch *touch, cocos2d::Event *event)
{
    removeFromParentAndCleanup(true);
}