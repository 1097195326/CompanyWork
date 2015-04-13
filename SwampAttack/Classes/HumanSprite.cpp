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
bool HumanSprite::init()
{
    if (!Sprite::init()) {
        return false;
    }
    
    return true;
}
void HumanSprite::setModel(Human *human)
{
    
}
void HumanSprite::update(float data)
{
    
}
void HumanSprite::run()
{
    runAction(m_actionData["runAction"]);
}
void HumanSprite::wait()
{
    runAction(m_actionData["waitAction"]);
}
void HumanSprite::shoot()
{
    runAction(m_actionData["shootAction"]);
}
void HumanSprite::reload()
{
    runAction(m_actionData["reloadAction"]);
}
void HumanSprite::reloadShotCall()
{
    
}
void HumanSprite::runShotCall()
{
    
}
void HumanSprite::shootShotCall()
{
    
}
void HumanSprite::waitShotCall()
{
    
}