//
//  WalkEnemySprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/23.
//
//

#include "WalkEnemySprite.h"
#include "BaseUtil.h"


WalkEnemySprite::WalkEnemySprite(string name,Enemy * model):EnemySprite(model)
{
    EnemyInfoData info = EnemyInfo::getInstance()->getInfoByName(name);
    float attackSpeed = m_model->getAttackSpeed();
    Action * walkAction = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_walk", info.walkFrames));
    walkAction->retain();
    if (name == "zombie") {
//        Action * hurtAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_walk", 10),
//                                               CallFunc::create(CC_CALLBACK_0(WalkEnemySprite::hurtCall, this)),
//                                               NULL);
        
        Action * hurtAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_hurt", 10),
                                              CallFunc::create(CC_CALLBACK_0(WalkEnemySprite::hurtCall, this)),
                                              NULL);
        hurtAction->retain();
        m_map["hurtAction"] = hurtAction;
    }
    
    
    Action * attackAction = RepeatForever::create(
                                  Spawn::create(
                                          Sequence::create(DelayTime::create(attackSpeed * info.attackFrame),
                                                           CallFunc::create(CC_CALLBACK_0(WalkEnemySprite::attackCall, this)), NULL),
                                          BaseUtil::makeAnimateWithNameIndexDelay(name + "_attack", info.attackFrames,attackSpeed),
                                          NULL)
                                                  );
    attackAction->retain();
    Action * dieAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_down", info.downFrames),
                                          CallFunc::create(CC_CALLBACK_0(WalkEnemySprite::dieCall, this)),
                                          NULL);
    dieAction->retain();
    
    
    m_map["walkAction"] = walkAction;
    m_map["attackAction"] = attackAction;
    m_map["dieAction"] = dieAction;
    
    
    scheduleUpdate();
}
void WalkEnemySprite::update(float data)
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
        removeFromParentAndCleanup(true);
        return;
    }
    if (m_model->isHurt()) {
        healthBar->setVisible(true);
        healthBar->updatePercent(m_model->getHealthPercent());
        hurt();
        setPosition(m_model->getPosition());
    }else
    {
        healthBar->setVisible(false);
    }
}
void WalkEnemySprite::hurt()
{
    if (m_model->getModelId() == "zombie")
    {
        if (actionStatus == isHurting) {
            return;
        }
        actionStatus = isHurting;
        stopAllActions();
        runAction(m_map["hurtAction"]);
    }
}
void WalkEnemySprite::move()
{
    if (actionStatus == isMoving) {
        return;
    }
    actionStatus = isMoving;
    stopAllActions();
    runAction(m_map["walkAction"]);
}
void WalkEnemySprite::attack()
{
    if (actionStatus == isAttacking) {
        return;
    }
    actionStatus = isAttacking;
    stopAllActions();
    runAction(m_map["attackAction"]);
}
void WalkEnemySprite::die()
{
    if (actionStatus == isDieing) {
        return;
    }
    actionStatus = isDieing;
    stopAllActions();
    runAction(m_map["dieAction"]);
}