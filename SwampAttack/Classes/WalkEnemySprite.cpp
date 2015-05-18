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
    m_map["walkAction"] = walkAction;
    Action * hurtHeavyAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_hurt_heavy", info.hurtHeavyFrames),
                                          CallFunc::create(CC_CALLBACK_0(WalkEnemySprite::hurtCall, this)),
                                          NULL);
    hurtHeavyAction->retain();
    m_map["hurtAction3"] = hurtHeavyAction;
    Action * hurtLightAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_hurt_light", info.hurtLightFrames),
                                                CallFunc::create(CC_CALLBACK_0(WalkEnemySprite::hurtCall, this)),
                                                NULL);
    hurtLightAction->retain();
    m_map["hurtAction2"] = hurtLightAction;
    Action * hurtOnAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_hurt_on", info.hurtOnFrames),
                                                CallFunc::create(CC_CALLBACK_0(WalkEnemySprite::hurtCall, this)),
                                                NULL);
    hurtOnAction->retain();
    m_map["hurtAction1"] = hurtOnAction;
    
    Action * attackAction = RepeatForever::create(
                                  Spawn::create(
                                          Sequence::create(DelayTime::create(attackSpeed * info.attackFrame),
                                                           CallFunc::create(CC_CALLBACK_0(WalkEnemySprite::attackCall, this)), NULL),
                                          BaseUtil::makeAnimateWithNameIndexDelay(name + "_attack", info.attackFrames,attackSpeed),
                                          NULL)
                                                  );
    attackAction->retain();
    m_map["attackAction"] = attackAction;
    Action * dieAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_down", info.downFrames),
                                          CallFunc::create(CC_CALLBACK_0(WalkEnemySprite::dieCall, this)),
                                          NULL);
    dieAction->retain();
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
    }else if (m_model->isHurt())
    {
        hurt();
    }
    if (m_model->isShowHurt())
    {
        healthBar->setVisible(true);
        healthBar->updatePercent(m_model->getHealthPercent());
    }else
    {
        healthBar->setVisible(false);
    }
}
void WalkEnemySprite::hurt()
{
    if (actionStatus == isHurting) {
        return;
    }
    actionStatus = isHurting;
    stopAllActions();
    int index = m_model->getHurtIndex();
    switch (index) {
        case 1:
            runAction(m_map["hurtAction1"]);
            break;
        case 2:
            runAction(m_map["hurtAction2"]);
            break;
        case 3:
            runAction(m_map["hurtAction3"]);
            break;
        default:
            break;
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