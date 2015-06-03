//
//  PropSprite.cpp
//  SwampAttack
//
//  Created by 张洪星 on 15/6/2.
//
//

#include "PropSprite.h"
#include "GameMapManager.h"
#include "GameFightScene.h"
#include "PropManager.h"
#include "GameMapManager.h"

PropSprite::PropSprite(Prop * prop):m_prop(prop),m_state(p_s_normal)
{
    init();
    m_propIcon = NULL;
    
    m_iconScale = 0.6;
    int iconIndex = PropManager::getInstance()->getTakeUpPropIndexByName(m_prop->getId());
    m_blueBg = Sprite::create(ImagePath("fight_gun_blueBg.png"));
    Sprite * propIcon = Sprite::create(ImagePath(StringUtils::format("%s_icon.png",m_prop->getModelId().c_str())));
    addChild(m_blueBg);
    addChild(propIcon,5);
    
    m_blueBg->setScale(m_iconScale);
    propIcon->setScale(0.5);
    
    Vec2 iconPoint = _G_M_M->fightScene_PropIcon_Position;
    float iconWidth = m_blueBg->getContentSize().width;
    m_blueBg->setPosition(iconPoint - Vec2(iconWidth * (iconIndex - 1), 0) * m_iconScale);
    propIcon->setPosition(iconPoint - Vec2(iconWidth * (iconIndex - 1), 0) * m_iconScale);
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(PropSprite::touchBegan, this);
    m_listener->onTouchMoved = CC_CALLBACK_2(PropSprite::touchMove, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(PropSprite::touchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, m_blueBg);
    
    
    updateData();
    _G_V->addChild(this,1);
    scheduleUpdate();
}
PropSprite::~PropSprite()
{
    if(m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
void PropSprite::update(float data)
{
    if (m_prop->isMoveEnd())
    {
        m_prop->setPropPoint(m_propIcon->getPosition());
    }
//    else if (m_prop->isArrve())
//    {
//        if (m_state != p_s_arrve) {
//            m_state = p_s_arrve;
//            m_propIcon->stopAllActions();
//            m_propIcon->removeFromParentAndCleanup(true);
//        }
//    }
    else if (m_prop->isThrowing())
    {
        throwProp();
    }
}
void PropSprite::throwProp()
{
    
}
void PropSprite::propArrveCall(Node * pSender)
{
    m_prop->arrveCall();
    Sprite * sprite = (Sprite *)pSender;
    sprite->stopAllActions();
    sprite->removeFromParentAndCleanup(true);
}
void PropSprite::propThrowCall(Node * pSender)
{
    log("prop throw call");
    m_state = p_s_normal;
    m_prop->throwCall();
    
//    Sprite * sprite = (Sprite *)pSender;
//    sprite->stopAllActions();
//    sprite->removeFromParentAndCleanup(true);
}
bool PropSprite::touchBegan(Touch *touch, Event *event)
{
    Vec2 p = m_blueBg->convertToNodeSpace(touch->getLocation());
    Rect r = Rect(0, 0, m_blueBg->getContentSize().width ,m_blueBg->getContentSize().height);
    if (r.containsPoint(p)) {
        m_propIcon = Sprite::create(ImagePath(StringUtils::format("%s_icon.png",m_prop->getModelId().c_str())));
        m_propIcon->setPosition(m_blueBg->getPosition());
        m_propIcon->setScale(0.5);
        addChild(m_propIcon,6);
        return true;
    }
    return false;
}
void PropSprite::touchMove(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Vec2 touchPoint = touch->getLocation();
    m_propIcon ->setPosition(touchPoint);
    if(m_prop->isMoveing())
    {
        m_prop->setPropPoint(touchPoint);
    }else
    {
        m_prop->setStateMoveing();
    }
}
void PropSprite::touchEnd(Touch *touch, Event *event)
{
//    log("prop modeld id:%s",m_prop->getModelId().c_str());
    if (m_prop->isMoveing())
    {
        m_prop->setStateMoveEnd();
        if (m_prop->isCanArrve())
        {
            m_prop->arrveCall();
        }else
        {
           ActionInterval * a1 = EaseBounceIn::create(MoveTo::create(0.3, Vec2(m_propIcon->getPositionX(), _G_M_M->fightScene_PropArrve_line)));
            ActionInterval * a2 = Sequence::create(a1,
                                                   CallFuncN::create(CC_CALLBACK_1(PropSprite::propArrveCall, this)), NULL);
            m_propIcon->runAction(a2);
        }
    }
}

void PropSprite::updateData()
{
    
    
    
}