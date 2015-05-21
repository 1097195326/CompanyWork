//
//  WalkEnemySprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/23.
//
//

#include "WalkEnemySprite.h"
#include "BaseUtil.h"


WalkEnemySprite::WalkEnemySprite(Enemy * model):EnemySprite(model)
{
    string name = m_model->getModelId();
    
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
    
    setArmorView();
    
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
    if (isHaveArmor && m_model->isWeak() && armorSprite) {
        isHaveArmor = false;
        string armorName = m_model->getCapId();
        EnemyInfoData info = EnemyInfo::getInstance()->getInfoByName(armorName);
        
        Layer * gameLayer =(Layer *) this->getParent();
        Sprite * armor = Sprite::createWithTexture(armorSprite->getTexture(),
                                                   armorSprite->getTextureRect());
        gameLayer->addChild(armor);
        armor->setPosition(this->getPosition() + Vec2(info.width * 0.5,info.height));
        
        armorSprite->stopAllActions();
        armorSprite->removeFromParentAndCleanup(true);
        ActionInterval * a0 = RotateTo::create(0.6, 180);
        ActionInterval * a1 = MoveBy::create(0.6, Vec2(100, 0));
        ActionInterval * a2 = EaseSineIn::create(MoveBy::create(0.6, Vec2(0, -90)));
        ActionInterval * a3 = Sequence::create(Spawn::create(a0,a1,a2, NULL),
                                               FadeOut::create(0.2), NULL);
        armor->runAction(a3);
    }
}
void WalkEnemySprite::setArmorView()
{
    string armorName = m_model->getCapId();
    if ((armorName.size() > 0)) {
        isHaveArmor = true;
        EnemyInfoData info = EnemyInfo::getInstance()->getInfoByName(armorName);
        armorSprite = Sprite::create();
        addChild(armorSprite);
        armorSprite->setPosition(info.width * 0.5,info.height);
        
        float attackSpeed = m_model->getAttackSpeed();
        Action * walkAction = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex(armorName + "_walk", info.walkFrames));
        walkAction->retain();
        m_map["armorWalkAction"] = walkAction;
        Action * hurtHeavyAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(armorName + "_hurt_heavy", info.hurtHeavyFrames),
                                                    CallFunc::create(CC_CALLBACK_0(WalkEnemySprite::hurtCall, this)),
                                                    NULL);
        hurtHeavyAction->retain();
        m_map["armorHurtAction3"] = hurtHeavyAction;
        Action * hurtLightAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(armorName + "_hurt_light", info.hurtLightFrames),
                                                    CallFunc::create(CC_CALLBACK_0(WalkEnemySprite::hurtCall, this)),
                                                    NULL);
        hurtLightAction->retain();
        m_map["armorHurtAction2"] = hurtLightAction;
        Action * hurtOnAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(armorName + "_hurt_on", info.hurtOnFrames),
                                                 CallFunc::create(CC_CALLBACK_0(WalkEnemySprite::hurtCall, this)),
                                                 NULL);
        hurtOnAction->retain();
        m_map["armorHurtAction1"] = hurtOnAction;
        
        Action * attackAction = RepeatForever::create(
                                                      Spawn::create(
                                                                    Sequence::create(DelayTime::create(attackSpeed * info.attackFrame),
                                                                                     CallFunc::create(CC_CALLBACK_0(WalkEnemySprite::attackCall, this)), NULL),
                                                                    BaseUtil::makeAnimateWithNameIndexDelay(armorName + "_attack", info.attackFrames,attackSpeed),
                                                                    NULL)
                                                      );
        attackAction->retain();
        m_map["armorAttackAction"] = attackAction;
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
            if (isHaveArmor) {
                armorSprite->stopAllActions();
                armorSprite->runAction(m_map["armorHurtAction1"]);
            }
            break;
        case 2:
            runAction(m_map["hurtAction2"]);
            if (isHaveArmor) {
                armorSprite->stopAllActions();
                armorSprite->runAction(m_map["armorHurtAction2"]);
            }
            break;
        case 3:
            runAction(m_map["hurtAction3"]);
            if (isHaveArmor) {
                armorSprite->stopAllActions();
                armorSprite->runAction(m_map["armorHurtAction3"]);
            }
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
    if (isHaveArmor) {
        armorSprite->stopAllActions();
        armorSprite->runAction(m_map["armorWalkAction"]);
    }
}
void WalkEnemySprite::attack()
{
    if (actionStatus == isAttacking) {
        return;
    }
    actionStatus = isAttacking;
    stopAllActions();
    runAction(m_map["attackAction"]);
    if (isHaveArmor) {
        armorSprite->stopAllActions();
        armorSprite->runAction(m_map["armorAttackAction"]);
    }
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