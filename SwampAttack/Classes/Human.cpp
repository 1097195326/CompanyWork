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



Human::Human()
{
    GameMap * gameMap = GameMapManager::getInstance()->getGameMap();
    m_point = gameMap->m_targetPoint;
    m_gun = GunManager::getInstance()->getCurrentGun();
    
    m_status = _waits;
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
    if (m_status & _waits) {
        
    }else if (m_status & _shoot)
    {
        
    }else if (m_status & _reload)
    {
        
    }
    
}
void Human::fire(Touch * touch,Event * event)
{
    m_touchStatus = _isTouching;
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
Vec2 Human::getPosition()
{
    return m_point;
}
void Human::reloadCall()
{
    
}
void Human::shootCall()
{
    
}
void Human::changeCall()
{
    
}
//---------
bool Human::isWait()
{
    return m_status & _waits;
}
bool Human::isRun()
{
    return m_status & _run;
}
bool Human::isReload()
{
    return m_status & _reload;
}
bool Human::isShoot()
{
    return m_status & _shoot;
}
bool Human::isChange()
{
    return m_status & _change;
}