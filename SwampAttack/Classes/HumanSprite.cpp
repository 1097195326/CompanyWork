//
//  HumanSprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/27.
//
//

#include "HumanSprite.h"
#include "BaseUtil.h"


HumanSprite::HumanSprite()
{
    init();
    setAnchorPoint(Vec2(0.5,0));
    
    Action * reloadAction = Sequence::create(
                                             BaseUtil::makeAnimateWithNameAndIndex("reload_shotgun", 10),
                                             CallFunc::create(CC_CALLBACK_0(HumanSprite::reloadShotCall, this)),
                                             NULL);
    reloadAction->retain();
    Action * runAction = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex("run_shotgun", 8));
    runAction->retain();
    Action * shootAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex("shoot_shotgun", 7),
                                            CallFunc::create(CC_CALLBACK_0(HumanSprite::shootShotCall, this)),
                                            NULL);
    shootAction->retain();
    Action * waitAction = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex("wait_shotgun", 10));
    waitAction->retain();
    
    m_actionData["reloadAction"] = reloadAction;
    m_actionData["runAction"] = runAction;
    m_actionData["shootAction"] = shootAction;
    m_actionData["waitAction"] = waitAction;
    
    
    scheduleUpdate();
}
HumanSprite::~HumanSprite()
{
    std::map<std::string, Action * >::iterator itr;
    for (itr = m_actionData.begin(); itr != m_actionData.end(); itr++) {
        Action * ac = itr->second;
        ac->release();
    }
    m_actionData.clear();

}
void HumanSprite::setModel(Human *human)
{
    m_human = human;
    setPosition(m_human->getPosition());
}
void HumanSprite::update(float data)
{
    if (m_human->isWait())
    {
        wait();
    }else if (m_human->isRun())
    {
        run();
    }else if (m_human->isReload())
    {
        reload();
    }else if (m_human->isShoot())
    {
        shoot();
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
}
void HumanSprite::reload()
{
    if (m_status == _isReloading) {
        return;
    }
    m_status = _isReloading;
    stopAllActions();
    runAction(m_actionData["reloadAction"]);
}
void HumanSprite::reloadShotCall()
{
    m_human->reloadCall();
}
void HumanSprite::runShotCall()
{
    
}
void HumanSprite::shootShotCall()
{
    m_human->shootCall();
}
void HumanSprite::waitShotCall()
{
    
}
void HumanSprite::changeCall()
{
    m_human->changeCall();
}