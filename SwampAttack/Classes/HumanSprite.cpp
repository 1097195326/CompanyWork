//
//  HumanSprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/27.
//
//

#include "HumanSprite.h"
#include "BaseUtil.h"
#include "GameFightScene.h"

HumanSprite::HumanSprite()
{
    init();
    setAnchorPoint(Vec2(0.5,0));
    
    scheduleUpdate();
//    log("human create");
}
HumanSprite::~HumanSprite()
{
    std::map<std::string, Action * >::iterator itr;
    for (itr = m_actionData.begin(); itr != m_actionData.end(); itr++) {
        Action * ac = itr->second;
        ac->release();
        log("ac retain:%d",ac->getReferenceCount());
    }
    m_actionData.clear();
//    log("human deleate");
}
void HumanSprite::setModel(Human *human)
{
    m_human = human;
    setPosition(m_human->getPosition());
    Gun * gun = m_human->getGun();
    GunActionData actionData = GunActionInfo::getInstance()->getInfoByName(gun->getModelId());
    
    Action * reloadAction = Sequence::create(
                                             BaseUtil::makeAnimateWithNameIndexDelay(StringUtils::format("reload_%s",gun->getModelId().c_str()),
                                                                                     actionData.reloadFrames,
                                                                                     gun->getReloadSpeed()),
                                             CallFunc::create(CC_CALLBACK_0(HumanSprite::reloadShotCall, this)),
                                             NULL);
    reloadAction->retain();
    Action * shootAction = NULL;
    if (gun->getWeaponType() == 1)
    {
        shootAction = Spawn::create(
                                    Sequence::create(DelayTime::create(gun->getFireRate() * actionData.attackFrame),
                                                     CallFunc::create(CC_CALLBACK_0(HumanSprite::shootShotCall, this)), NULL),
                                    BaseUtil::makeAnimateWithNameIndexDelay(StringUtils::format("attack_%s",gun->getModelId().c_str()),
                                                                            actionData.attackFrames,
                                                                            gun->getFireRate()),
                                    NULL);
        shootAction->retain();
    }else
    {
        shootAction = Spawn::create(
                                    Sequence::create(DelayTime::create(gun->getFireRate() * actionData.attackFrame),
                                                     CallFunc::create(CC_CALLBACK_0(HumanSprite::shootShotCall, this)), NULL),
                                    BaseUtil::makeAnimateWithNameIndexDelay(StringUtils::format("shoot_%s",gun->getModelId().c_str()),
                                                                            actionData.attackFrames,
                                                                            gun->getFireRate()),
                                    NULL);
        shootAction->retain();
    }
    
    
    Action * waitAction = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex(StringUtils::format("wait_%s",gun->getModelId().c_str()),
                                                                                      actionData.waitFrames));
    waitAction->retain();
    
    Action * runAction = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex("run_qiang3", 8));
    runAction->retain();
    
    Action * changeAction = Sequence::create(
                                             BaseUtil::makeAnimateWithNameIndexDelay(StringUtils::format("reload_%s",gun->getModelId().c_str()),
                                                                                     actionData.reloadFrames,
                                                                                     gun->getReloadSpeed()),
                                             CallFunc::create(CC_CALLBACK_0(HumanSprite::changeCall, this)),
                                             NULL);
    changeAction->retain();
    
    Action * throwAction = RepeatForever::create(
                                                 Spawn::create(
                                         Sequence::create(DelayTime::create(0.08 * 7),
                                                          CallFunc::create(CC_CALLBACK_0(HumanSprite::throwEndCall, this)), NULL),
                                         BaseUtil::makeAnimateWithNameIndexDelay("throw", 9,0.08),
                                         NULL)
                                                 );
//    Action * throwAction = RepeatForever::create(BaseUtil::makeAnimateWithNameIndexDelay("throw", 9,0.08));
    throwAction->retain();
    
    m_actionData["reloadAction"] = reloadAction;
    m_actionData["shootAction"] = shootAction;
    m_actionData["waitAction"] = waitAction;
    m_actionData["changeAction"] = changeAction;
    m_actionData["throwAction"] = throwAction;
    
    m_actionData["runAction"] = runAction;
    
    _G_V->addChild(this,4);
}
void HumanSprite::update(float data)
{
    if (m_human->isChange())
    {
        change();
    }else if (m_human->isWait())
    {
        wait();
    }else if (m_human->isRun())
    {
        setPosition(m_human->getPosition());
        run();
    }else if (m_human->isReload())
    {
        reload();
    }else if (m_human->isShoot())
    {
        shoot();
    }else if (m_human->isThrowing())
    {
        throwProp();
    }
}
void HumanSprite::wait()
{
    if (m_status == _isWaiting) {
        return;
    }
    m_status = _isWaiting;
    stopAllActions();
    runAction(m_actionData["waitAction"]);
}
void HumanSprite::run()
{
    if (m_status == _isRuning) {
        return;
    }
    m_status = _isRuning;
    stopAllActions();
    runAction(m_actionData["runAction"]);
}
void HumanSprite::shoot()
{
    if (m_status == _isShooting) {
        return;
    }
    m_status = _isShooting;
    stopAllActions();
    runAction(m_actionData["shootAction"]);

//    string yinxiao = StringUtils::format("%s_shoot.mp3",m_human->getGun()->getModelId().c_str());
//    SimpleAudioEngine::getInstance()->playEffect(MusicPath(yinxiao).c_str());
}
void HumanSprite::reload()
{
    if (m_status == _isReloading) {
        return;
    }
    m_status = _isReloading;
    stopAllActions();
    runAction(m_actionData["reloadAction"]);
    
    string yinxiao = StringUtils::format("%s_reload.mp3",m_human->getGun()->getModelId().c_str());
    SimpleAudioEngine::getInstance()->playEffect(MusicPath(yinxiao).c_str());
}
void HumanSprite::change()
{
    if (m_status == _isChangeing) {
        return;
    }
    m_status = _isChangeing;
    stopAllActions();
    changeActions();
    runAction(m_actionData["changeAction"]);
}
void HumanSprite::throwProp()
{
    if (m_status == _isThrowProp) {
        return;
    }
    m_status = _isThrowProp;
    stopAllActions();
    runAction(m_actionData["throwAction"]);
}
void HumanSprite::changeActions()
{
    m_actionData["reloadAction"]->release();
    m_actionData["shootAction"]->release();
    m_actionData["waitAction"]->release();
    m_actionData["changeAction"]->release();
    
    Gun * gun = m_human->getGun();
    GunActionData actionData = GunActionInfo::getInstance()->getInfoByName(gun->getModelId());
    
    Action * reloadAction = Sequence::create(
                                             BaseUtil::makeAnimateWithNameIndexDelay(StringUtils::format("reload_%s",gun->getModelId().c_str()),
                                                                                     actionData.reloadFrames,
                                                                                     gun->getReloadSpeed()),
                                             CallFunc::create(CC_CALLBACK_0(HumanSprite::reloadShotCall, this)),
                                             NULL);
    reloadAction->retain();
    
    Action * shootAction = NULL;
    if (gun->getWeaponType() == 1)
    {
        shootAction = Spawn::create(
                                    Sequence::create(DelayTime::create(gun->getFireRate() * actionData.attackFrame),
                                                     CallFunc::create(CC_CALLBACK_0(HumanSprite::shootShotCall, this)), NULL),
                                    BaseUtil::makeAnimateWithNameIndexDelay(StringUtils::format("attack_%s",gun->getModelId().c_str()),
                                                                            actionData.attackFrames,
                                                                            gun->getFireRate()),
                                    NULL);
        shootAction->retain();
    }else
    {
        shootAction = Spawn::create(
                                    Sequence::create(DelayTime::create(gun->getFireRate() * actionData.attackFrame),
                                                     CallFunc::create(CC_CALLBACK_0(HumanSprite::shootShotCall, this)), NULL),
                                    BaseUtil::makeAnimateWithNameIndexDelay(StringUtils::format("shoot_%s",gun->getModelId().c_str()),
                                                                            actionData.attackFrames,
                                                                            gun->getFireRate()),
                                    NULL);
        shootAction->retain();
    }
    
    Action * waitAction = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex(StringUtils::format("wait_%s",gun->getModelId().c_str()),
                                                                                      actionData.waitFrames));
    waitAction->retain();
    
    Action * changeAction = Sequence::create(
                                             BaseUtil::makeAnimateWithNameIndexDelay(StringUtils::format("reload_%s",gun->getModelId().c_str()),
                                                                                     actionData.reloadFrames,
                                                                                     gun->getReloadSpeed()),
                                             CallFunc::create(CC_CALLBACK_0(HumanSprite::changeCall, this)),
                                             NULL);
    changeAction->retain();
    
    m_actionData["reloadAction"] = reloadAction;
    m_actionData["shootAction"] = shootAction;
    m_actionData["waitAction"] = waitAction;
    m_actionData["changeAction"] = changeAction;
}
void HumanSprite::reloadShotCall()
{
    m_status = _normal;
    m_human->reloadCall();
}
void HumanSprite::runShotCall()
{
    
}
void HumanSprite::shootShotCall()
{
    string yinxiao = StringUtils::format("%s_shoot.mp3",m_human->getGun()->getModelId().c_str());
    SimpleAudioEngine::getInstance()->playEffect(MusicPath(yinxiao).c_str());
    m_status = _normal;
    m_human->shootCall();
    
}
void HumanSprite::waitShotCall()
{
    
}
void HumanSprite::changeCall()
{
    m_status = _normal;
    m_human->changeCall();
}
void HumanSprite::throwEndCall()
{
    m_status = _normal;
    m_human->throwPropCall();
}