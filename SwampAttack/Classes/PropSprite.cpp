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

PropSprite::PropSprite(string propId):m_state(p_s_normal)
{
    init();
    m_prop = PropManager::getInstance()->addUsingProp(propId);
    
    m_iconScale = 0.5;
    m_propIcon = Sprite::create(ImagePath(StringUtils::format("%s_icon.png",m_prop->getModelId().c_str())));

    addChild(m_propIcon,5);
    m_propIcon->setScale(0.5);
    
    scheduleUpdate();
}
PropSprite::~PropSprite()
{
    
}
void PropSprite::update(float data)
{
    if (m_prop == NULL) {
        return;
    }
    if (m_prop->isMoveing())
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
    }else if (m_prop->isReadyToHurt())
    {
        readyToHurt();
    }else if (m_prop->isDie())
    {
        m_prop->setStateCanDelete();
        removeFromParentAndCleanup(true);
    }
}
void PropSprite::throwProp()
{
    m_state = p_s_normal;
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
    
}
void PropSprite::readyToHurt()
{
    
}
void PropSprite::moveIng(cocos2d::Vec2 point)
{
    m_propIcon->setPosition(point);
}
void PropSprite::moveEnd()
{
    m_prop->setPropPoint(m_propIcon->getPosition());
    if (m_prop->isCanArrve())
    {
        m_prop->arrveCall();
        m_propIcon->stopAllActions();
        m_propIcon->removeFromParentAndCleanup(true);
    }else
    {
        m_prop->setStateMoveing();
        ActionInterval * a1 = EaseBounceIn::create(MoveTo::create(0.3, Vec2(m_propIcon->getPositionX(), _G_M_M->fightScene_PropArrve_line)));
        ActionInterval * a2 = Sequence::create(a1,
                                               CallFuncN::create(CC_CALLBACK_1(PropSprite::propArrveCall, this)), NULL);
        m_propIcon->runAction(a2);
    }
}

