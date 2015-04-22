//
//  EnemySprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "EnemySprite.h"
#include "BaseUtil.h"



EnemySprite::EnemySprite(string name)
{
    init();
    setAnchorPoint(Vec2(0.5,0));
    
    Action * walkAction = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_walk", 14));
    walkAction->retain();
    
    Action * attackAction = RepeatForever::create(Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_attack", 12),
                                             CallFunc::create(CC_CALLBACK_0(EnemySprite::attackCall, this)),
                                             NULL));
    
//    Action * shootAction = Spawn::create(
//                                         Sequence::create(DelayTime::create(0.08 * 8),
//                                                          CallFunc::create(CC_CALLBACK_0(EnemySprite::attackCall, this)), NULL),
//                                         BaseUtil::makeAnimateWithNameIndexDelay(name + "_attack", 12,0.1),
//                                         NULL);
    attackAction->retain();
    Action * dieAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_down", 14),
                                          CallFunc::create(CC_CALLBACK_0(EnemySprite::dieCall, this)),
                                          NULL);
    dieAction->retain();
    
    m_map["walkAction"] = walkAction;
    m_map["attackAction"] = attackAction;
    m_map["dieAction"] = dieAction;
    

    healthBar = new ProgressBar("xuenei.png","xuewai.png");
    healthBar->ignoreAnchorPointForPosition(true);
    addChild(healthBar,1);
    healthBar->setVisible(false);
    
    scheduleUpdate();
}
EnemySprite::~EnemySprite()
{
    std::map<std::string, Action * >::iterator itr;
    for (itr = m_map.begin(); itr != m_map.end(); itr++) {
        Action * ac = itr->second;
        ac->release();
    }
    m_map.clear();
    
    removeAllChildrenWithCleanup(true);
    delete healthBar;
}
void EnemySprite::update(float data)
{
    if (m_model->isDieing())
    {
        die();
    }else if (m_model->isWalk())
    {
        setPosition(m_model->getPosition());
        move();
    }else if (m_model->isAttack())
    {
        attack();
    }else if (m_model->isDied())
    {
        m_model->diedCall();
        unscheduleUpdate();
        removeFromParentAndCleanup(false);
        delete this;
        return;
    }
    if (m_model->isHurt()) {
        healthBar->setVisible(true);
        healthBar->updatePercent(m_model->getHealthPercent());
    }else
    {
        healthBar->setVisible(false);
    }
}
void EnemySprite::setMode(Enemy *model)
{
    m_model = model;
    int w = m_model->getWidth();
    int h = m_model->getHeight();
    healthBar->setPosition(Vec2(w * 0.5, h * 0.9));
}
void EnemySprite::move()
{
    if (actionStatus == isMoving) {
        return;
    }
    actionStatus = isMoving;
    stopAllActions();
    runAction(m_map["walkAction"]);
}
void EnemySprite::attack()
{
    if (actionStatus == isAttacking) {
        return;
    }
    actionStatus = isAttacking;
    stopAllActions();
    runAction(m_map["attackAction"]);
}
void EnemySprite::die()
{
    if (actionStatus == isDieing) {
        return;
    }
    actionStatus = isDieing;
    stopAllActions();
    runAction(m_map["dieAction"]);
}
void EnemySprite::attackCall()
{
    
}
void EnemySprite::dieCall()
{
    m_model->dieingCall();
}