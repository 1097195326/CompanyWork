//
//  Human.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "Human.h"
#include "GameMapManager.h"
#include "HumanSprite.h"


#include "HumanWaitState.h"
#include "HumanShootState.h"
#include "HumanReloadState.h"
#include "HumanChangeState.h"
#include "HumanThrowPropState.h"


Human::Human()
{
    GameMap * gameMap = GameMapManager::getInstance()->getGameMap();
    m_point = gameMap->fightScene_human_Point;
    m_gun = GunManager::getInstance()->getCurrentGun();
    
    m_status = _h_waits;
    m_state = HumanWaitState::getInstance();
    m_touchStatus = _t_normal;
    
}
Human::~Human()
{
    
}
Human * Human::getInstance()
{
    static Human human;
    return &human;
}
void Human::gameLoop(float data)
{
    // other status first
    
    // ---
    m_state->Execute(this);
    
}
void Human::resetData()
{
    stop();
    changeState(HumanWaitState::getInstance());
    
}
void Human::changeState(State<Human> *state)
{
    state->Enter(this);
    m_state = state;
}
void Human::fire(Touch * touch,Event * event)
{
    m_fireToPoint = touch->getLocation();
    GameMap * gameMap = GameMapManager::getInstance()->getGameMap();
    if (gameMap->m_BulletStartPoint.x > m_fireToPoint.x)
    {
        m_touchStatus = _touchEnd;
        return;
    }
    if (m_touchStatus == _isTouching)
    {
        return;
    }
    m_touchStatus = _isTouching;
}
void Human::stop()
{
    m_touchStatus = _touchEnd;
//    string yinxiao = StringUtils::format("%s_shoot.mp3",m_gun->getModelId().c_str());
//    SimpleAudioEngine::getInstance()->stopAllEffects();
}
void Human::changeGun(Gun *gun)
{
    m_gun = gun;
    changeState(HumanChangeState::getInstance());
}
Gun * Human::getGun()
{
    return m_gun;
}
void Human::throwProp(Prop *prop)
{
    if (! isChange()) {
        changeState(HumanThrowPropState::getInstance());
    }
    m_throwPropStack.push(prop);
}
void Human::setView()
{
    HumanSprite * sprite = new HumanSprite();
    sprite->setModel(this);
    sprite->autorelease();
}
///---- interface for view call back
void Human::reloadCall()
{
    m_gun->reloadBullet();
    m_waitingTime = m_gun->getReloadWaitingTime();
    m_status = _h_reloaded;
}
void Human::shootCall()
{
    m_status = _h_shooted;
    bool isHaveBullet = m_gun->fire(m_fireToPoint);
    if (isHaveBullet) {
        //  枪 有子弹 可以继续使用
//        log("shoot call have bullet");
        m_waitingTime = m_gun->getFireWaitingTime();
//        log("wait time :%f",m_waitingTime);
    }else
    {
        // 枪 没有子弹了，请切换到 默认 枪
//        log("shoot call no bullet");
        if (!m_gun->isDefaultGun())
        {
            GunManager::getInstance()->changeGun(defaultGunID);
        }
    }
    
//    log("shoot call");
}
void Human::changeCall()
{
    m_status = _h_changed;
}
void Human::throwPropCall()
{
    Prop * throwProp = m_throwPropStack.front();
    m_throwPropStack.pop();
    if (m_throwPropStack.empty())
    {
        m_status = _h_throwed;
    }
    throwProp->setStateThrowing();
}
//---- interface for state
float Human::getWaitingTime()
{
//    log("m_waiting time :%f",m_waitingTime);
    return m_waitingTime;
}
void Human::minusWaitingTime()
{
    m_waitingTime -= 0.055;
}
void Human::setStateReload()
{
    m_status = _h_reloading;
}
void Human::setStateShoot()
{
    m_status = _h_shooting;
}
void Human::setStateWait()
{
    m_status = _h_waits;
}
void Human::setStateChange()
{
    m_status = _h_changeing;
}
void Human::setStateThrow()
{
    m_status = _h_throwing;
}
bool Human::isTouching()
{
    return m_touchStatus == _isTouching;
}
bool Human::isTouchEnd()
{
    return m_touchStatus == _touchEnd;
}
bool Human::isFull()
{
    return m_gun->isFull();
}
bool Human::isHaveBullet()
{
    return m_gun->isHaveBullet();
}
bool Human::isShooted()
{
    return m_status == _h_shooted;
}
bool Human::isChanged()
{
    return m_status == _h_changed;
}
bool Human::isThrowEnd()
{
    return m_status == _h_throwed;
}
//------- interface for view
Vec2 Human::getPosition()
{
    return m_point;
}
bool Human::isWait()
{
    return m_status == _h_waits;
}
bool Human::isRun()
{
    return m_status == _h_run;
}
bool Human::isReload()
{
    return m_status == _h_reloading;
}
bool Human::isReloaded()
{
    return m_status == _h_reloaded;
}
bool Human::isShoot()
{
    return m_status == _h_shooting;
}
bool Human::isChange()
{
    return m_status == _h_changeing;
}
bool Human::isThrowing()
{
    return m_status == _h_throwing;
}