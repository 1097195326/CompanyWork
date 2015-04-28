//
//  FlyEnemySprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/23.
//
//

#include "FlyEnemySprite.h"
#include "BaseUtil.h"


FlyEnemySprite::FlyEnemySprite(string name,Enemy * model):EnemySprite(model)
{
    EnemyInfoData info = EnemyInfo::getInstance()->getInfoByName(name);
    float attackSpeed = m_model->getAttackSpeed();
    
    Action * walkAction = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_fly", info.walkFrames));
    walkAction->retain();
    
    Action * attackAction = Spawn::create(
                                          Sequence::create(DelayTime::create(attackSpeed * info.attackFrame),
                                                           CallFunc::create(CC_CALLBACK_0(FlyEnemySprite::attackCall, this)), NULL),
                                          BaseUtil::makeAnimateWithNameIndexDelay(name + "_attack", info.attackFrames,attackSpeed),
                                          NULL);
    attackAction->retain();
//    Action * dieAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_down", info.downFrames),
//                                          CallFunc::create(CC_CALLBACK_0(FlyEnemySprite::dieCall, this)),
//                                          NULL);
//    dieAction->retain();
    
    m_map["walkAction"] = walkAction;
    m_map["attackAction"] = attackAction;
//    m_map["dieAction"] = dieAction;
    
    
    scheduleUpdate();
    
}
void FlyEnemySprite::update(float data)
{
    if (m_model->isDieing())
    {
        die();
    }else if (m_model->isAttack())
    {
        attack();
    }else if (m_model->isWalk())
    {
        move();
    }else if (m_model->isDied())
    {
        m_model->diedCall();
        unscheduleUpdate();
        removeFromParentAndCleanup(true);
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
    setPosition(m_model->getPosition());
}
void FlyEnemySprite::move()
{
    if (actionStatus == isMoving) {
        return;
    }
    actionStatus = isMoving;
    stopAllActions();
    runAction(m_map["walkAction"]);
}
void FlyEnemySprite::attack()
{
    if (actionStatus == isAttacking) {
        return;
    }
    actionStatus = isAttacking;
    stopAllActions();
    runAction(m_map["attackAction"]);
}
void FlyEnemySprite::die()
{
    
    if (actionStatus == isDieing) {
        return;
    }
    actionStatus = isDieing;
    dieCall();
//    stopAllActions();
//    runAction(m_map["dieAction"]);
}