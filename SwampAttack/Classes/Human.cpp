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
#include "GameDirector.h"


#include "HumanWaitState.h"
#include "HumanShootState.h"
#include "HumanReloadState.h"


Human::Human()
{
    GameMap * gameMap = GameMapManager::getInstance()->getGameMap();
    m_point = gameMap->m_targetPoint;
    m_gun = GunManager::getInstance()->getCurrentGun();
    
    m_status = _h_waits;
    m_state = HumanWaitState::getInstance();
    m_touchStatus = _t_normal;
    
    setView();
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
void Human::changeState(State<Human> *state)
{
    state->Enter(this);
    m_state = state;
}
void Human::fire(Touch * touch,Event * event)
{
    if (m_touchStatus == _isTouching)
    {
        return;
    }
    m_touchStatus = _isTouching;
    m_fireToPoint = touch->getLocation();
}
void Human::stop()
{
    m_touchStatus = _touchEnd;
}
void Human::changeGun(Gun *gun)
{
    
}
void Human::setView()
{
    HumanSprite * sprite = new HumanSprite();
    sprite->setModel(this);
    _G_D->addChild(sprite);
}
///---- interface for view call back
void Human::reloadCall()
{
    m_gun->addBullet();
//    m_status = _h_reloaded;
}
void Human::shootCall()
{
    m_gun->fire(m_fireToPoint);
    m_status = _h_shooted;
}
void Human::changeCall()
{
    
}
//---- interface for state
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
//bool Human::isReloaded()
//{
//    return m_status == _h_reloaded;
//}
bool Human::isShoot()
{
    return m_status == _h_shooting;
}
bool Human::isShooted()
{
    return m_status == _h_shooted;
}
bool Human::isChange()
{
    return m_status == _h_changeing;
}