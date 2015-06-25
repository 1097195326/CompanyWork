//
//  DropPropSprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/24.
//
//

#include "DropPropSprite.h"
#include "GameFightScene.h"
#include "BaseUtil.h"


DropPropSprite::DropPropSprite(Prop * prop)
{
    init();
    m_prop = prop;
    string modelId = m_prop->getModelId();
    
    m_icon = Sprite::create(ImagePath(StringUtils::format("%s_icon.png",modelId.c_str())));
    m_icon->setScale(0.5);
    addChild(m_icon,1);
    
    Action * guangAc = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex("item_flash", 4),
                                        CallFuncN::create(CC_CALLBACK_1(DropPropSprite::guangEnd, this)),
                                        NULL);
    Sprite * texiao = Sprite::create();
    addChild(texiao);
    texiao->runAction(guangAc);
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(DropPropSprite::touchBegan, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(DropPropSprite::touchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
    
    runAction(JumpBy::create(0.5, Vec2(0, 0), 50, 3));
    
    _G_V->addChild(this,640);
}
DropPropSprite::~DropPropSprite()
{
    if (m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
void DropPropSprite::guangEnd(cocos2d::Node *pSender)
{
    pSender->stopAllActions();
    pSender->removeFromParentAndCleanup(true);
}
bool DropPropSprite::touchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Vec2 point = m_icon->convertToNodeSpace(touch->getLocation());
    Rect rect = Rect(0, 0, m_icon->getContentSize().width, m_icon->getContentSize().height);
    if (rect.containsPoint(point))
    {
        //        log("money sprite touch");
        return true;
    }
    return false;
}
void DropPropSprite::touchEnd(cocos2d::Touch *touch, cocos2d::Event *event)
{
    stopAllActions();
    Vec2 m_p = getPosition();
    Vec2 t_p = m_prop->getPropViewPoint();
    
    float dis = t_p.getDistance(m_p);
    float  time = dis * 0.001;
    
    Action * ac = Sequence::create(Spawn::create(EaseSineIn::create(MoveTo::create(time, t_p)),
                                                 EaseSineIn::create(ScaleTo::create(time,0.1)),
                                                 NULL),
                                   CallFuncN::create(CC_CALLBACK_1(DropPropSprite::moveEnd, this)),
                                   NULL);
    runAction(ac);
    
    
}
void DropPropSprite::moveEnd(cocos2d::Node *pSender)
{
    m_prop->addProp();
    pSender->stopAllActions();
    removeFromParentAndCleanup(true);
}