//
//  CrumpEnemySprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/26.
//
//

#include "CrumpEnemySprite.h"
#include "BuffSprite.h"
#include "GameMapManager.h"


CrumpEnemySprite::CrumpEnemySprite(Enemy * model):EnemySprite(model)
{
    string name = m_model->getModelId();
    
    EnemyInfoData info = EnemyInfo::getInstance()->getInfoByName(name);
    float attackSpeed = m_model->getAttackSpeed();
    Action * walkAction = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_run", info.walkFrames));
    walkAction->retain();
    m_map["walkAction"] = walkAction;
    Action * hurtHeavyAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_hurt_heavy", info.hurtHeavyFrames),
                                                CallFunc::create(CC_CALLBACK_0(CrumpEnemySprite::hurtCall, this)),
                                                NULL);
    hurtHeavyAction->retain();
    m_map["hurtAction3"] = hurtHeavyAction;
    Action * hurtLightAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_hurt_light", info.hurtLightFrames),
                                                CallFunc::create(CC_CALLBACK_0(CrumpEnemySprite::hurtCall, this)),
                                                NULL);
    hurtLightAction->retain();
    m_map["hurtAction2"] = hurtLightAction;
    Action * hurtOnAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_hurt_on", info.hurtOnFrames),
                                             CallFunc::create(CC_CALLBACK_0(CrumpEnemySprite::hurtCall, this)),
                                             NULL);
    hurtOnAction->retain();
    m_map["hurtAction1"] = hurtOnAction;
    
    Action * attackAction = Sequence::create(
                                              Spawn::create(
                                                            Sequence::create(DelayTime::create(attackSpeed * info.attackFrame),
                                                                             CallFunc::create(CC_CALLBACK_0(CrumpEnemySprite::attackCall, this)), NULL),
                                                            BaseUtil::makeAnimateWithNameIndexDelay("explosion", info.attackFrames,attackSpeed),
                                                            NULL),
                                             NULL
                                            );
    attackAction->retain();
    m_map["attackAction"] = attackAction;
    Action * dieAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex("explosion", info.downFrames),
                                          CallFunc::create(CC_CALLBACK_0(CrumpEnemySprite::dieCall, this)),
                                          NULL);
    dieAction->retain();
    m_map["dieAction"] = dieAction;
    
    ActionInterval * shan = BaseUtil::makeAnimateWithNameAndIndex(name + "_Electric", 2);
    Action * dianjiAction = Sequence::create(shan,
                                             shan,
                                             CallFunc::create(CC_CALLBACK_0(CrumpEnemySprite::dianjiCall, this)),
                                             NULL
                                             );
    dianjiAction->retain();
    m_map["dianjiAction"] = dianjiAction;
    
    setArmorView();
    
    scheduleUpdate();
}
void CrumpEnemySprite::update(float data)
{
    if (m_model->isStopGame())
    {
        return;
    }
    if (m_model->isDieing())
    {
        die();
    }else if (m_model->isWalk())
    {
        setPosition(m_model->getPosition());
        move();
    }else if (m_model->isDianji())
    {
        dianji();
    }else if (m_model->isTanfei())
    {
        tanfei();
    }else if (m_model->isAttack())
    {
        attack();
    }else if (m_model->isDied())
    {
        m_model->diedCall();
        unscheduleUpdate();
        stopAllActions();
        removeAllChildrenWithCleanup(true);
        removeFromParentAndCleanup(true);
        return;
    }else if (m_model->isHurt())
    {
        hurt();
    }
    if (m_model->isHaveBuff())
    {
        showBuff();
    }
    if (m_model->isShowHurt())
    {
        healthBar->setVisible(true);
        healthBar->updatePercent(m_model->getHealthPercent());
    }else
    {
        healthBar->setVisible(false);
    }
    if (!m_model->isDianji() && isHaveArmor && armorSprite->getOpacity() == 0) {
        armorSprite->setOpacity(255);
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
void CrumpEnemySprite::setArmorView()
{
    string armorName = m_model->getCapId();
    if ((armorName.size() > 0)) {
        isHaveArmor = true;
        EnemyInfoData info = EnemyInfo::getInstance()->getInfoByName(armorName);
        armorSprite = Sprite::create();
        addChild(armorSprite);
        armorSprite->setPosition(0,info.height);
        
        Action * walkAction = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex(armorName + "_run", info.walkFrames));
        walkAction->retain();
        m_map["armorWalkAction"] = walkAction;
        Action * hurtHeavyAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(armorName + "_hurt_heavy", info.hurtHeavyFrames),
                                                    NULL);
        hurtHeavyAction->retain();
        m_map["armorHurtAction3"] = hurtHeavyAction;
        Action * hurtLightAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(armorName + "_hurt_light", info.hurtLightFrames),
                                                    NULL);
        hurtLightAction->retain();
        m_map["armorHurtAction2"] = hurtLightAction;
        Action * hurtOnAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(armorName + "_hurt_on", info.hurtOnFrames),
                                                 NULL);
        hurtOnAction->retain();
        m_map["armorHurtAction1"] = hurtOnAction;
    }
}
void CrumpEnemySprite::showBuff()
{
    std::list<GameBuff *> buffs = m_model->getBuffData();
    std::list<GameBuff *>::iterator iter;
    for (iter = buffs.begin(); iter != buffs.end();iter++)
    {
        GameBuff * buff = *iter;
        if (buff->isShow()) {
            
        }else
        {
            log("sprite add buff ");
            buff->setIsShow();
            
            BuffSprite * buffS = new BuffSprite(buff);
            buffS->autorelease();
            buffSprite->addChild(buffS);
        }
    }
}
void CrumpEnemySprite::hurt()
{
    if (actionStatus == isHurting) {
        return;
    }
    actionStatus = isHurting;
    guaiwuSprite->stopAllActions();
    int index = m_model->getHurtIndex();
    switch (index) {
        case 1:
            guaiwuSprite->runAction(m_map["hurtAction1"]);
            if (isHaveArmor) {
                armorSprite->stopAllActions();
                armorSprite->runAction(m_map["armorHurtAction1"]);
            }
            break;
        case 2:
            guaiwuSprite->runAction(m_map["hurtAction2"]);
            if (isHaveArmor) {
                armorSprite->stopAllActions();
                armorSprite->runAction(m_map["armorHurtAction2"]);
            }
            break;
        case 3:
            guaiwuSprite->runAction(m_map["hurtAction3"]);
            if (isHaveArmor) {
                armorSprite->stopAllActions();
                armorSprite->runAction(m_map["armorHurtAction3"]);
            }
            break;
        default:
            break;
    }
    texiaoSprite->stopAllActions();
    texiaoSprite->setVisible(true);
    texiaoSprite->runAction(texiaoAction);
}
void CrumpEnemySprite::move()
{
    if (actionStatus == isMoving) {
        return;
    }
    actionStatus = isMoving;
    guaiwuSprite->stopAllActions();
    guaiwuSprite->runAction(m_map["walkAction"]);
    if (isHaveArmor) {
        armorSprite->stopAllActions();
        armorSprite->runAction(m_map["armorWalkAction"]);
    }
}
void CrumpEnemySprite::dianji()
{
    if (actionStatus == isDianji) {
        return;
    }
    actionStatus = isDianji;
    guaiwuSprite->stopAllActions();
    guaiwuSprite->runAction(m_map["dianjiAction"]);
    if (isHaveArmor) {
        armorSprite->setOpacity(0);
    }
}
void CrumpEnemySprite::tanfei()
{
    if (actionStatus == isTanfei) {
        return;
    }
    actionStatus = isTanfei;
    
    guaiwuSprite->stopAllActions();
    if (isHaveArmor) {
        armorSprite->stopAllActions();
    }
    Vec2 startPoint = m_model->getPosition();
    Vec2 tagetPoint = _G_M_M->enemy_tanfei_targetPoint;
    tagetPoint.y = (tagetPoint.x - startPoint.x) * 0.8;
    
    float tatolTime = (tagetPoint.x - startPoint.x) * 0.001;
    
    ccBezierConfig conf;
    conf.controlPoint_1 = Vec2(startPoint.x + (tagetPoint.x - startPoint.x) * 0.4,
                               startPoint.y + (tagetPoint.x - startPoint.x) * 0.4);
    conf.controlPoint_2 = Vec2(startPoint.x + (tagetPoint.x - startPoint.x) * 0.6,
                               startPoint.y + (tagetPoint.x - startPoint.x) * 0.6);
    conf.endPosition =tagetPoint;
    ActionInterval * a1 = BezierTo::create(tatolTime, conf);
    
    ActionInterval * a2 = RotateTo::create(tatolTime, 270);
    
    runAction(Sequence::create(Spawn::create(a1,a2, NULL),
                               CallFuncN::create(CC_CALLBACK_0(CrumpEnemySprite::dieCall, this)),NULL));
}
void CrumpEnemySprite::attack()
{
    if (actionStatus == isAttacking) {
        return;
    }
    actionStatus = isAttacking;
    guaiwuSprite->stopAllActions();
    guaiwuSprite->runAction(m_map["attackAction"]);
    if (isHaveArmor && armorSprite) {
        armorSprite->stopAllActions();
        armorSprite->setVisible(false);
    }
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("boom.mp3").c_str());
}
void CrumpEnemySprite::die()
{
    if (actionStatus == isDieing) {
        return;
    }
    actionStatus = isDieing;
    guaiwuSprite->stopAllActions();
    guaiwuSprite->runAction(m_map["dieAction"]);
    
    texiaoSprite->stopAllActions();
    texiaoSprite->setVisible(true);
    texiaoSprite->runAction(texiaoAction);
    if (isHaveArmor && armorSprite) {
        isHaveArmor = false;
        armorSprite->stopAllActions();
        armorSprite->removeFromParentAndCleanup(true);
    }
    
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("boom.mp3").c_str());
}