//
//  Human.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#ifndef __SwampAttack__Human__
#define __SwampAttack__Human__

#include "GameObject.h"
#include "BaseCode.h"
#include "GunManager.h"


enum HumanStatus
{
    _clear  = 0b00000000,
    _waits  = 0b00000001,
    _run    = 0b00000010,
    _reload = 0b00000100,
    _shoot  = 0b00001000,
    _change = 0b00010000,
    
};
enum TouchStatus
{
    _t_normal,
    _isTouching,
    _touchEnd,
};
class Human : public GameObject {
private:
    int     m_status;
    TouchStatus m_touchStatus;
    Vec2    m_point;
    Gun *   m_gun;
private:
    void    setView();
    
public:
    Vec2    getPosition();
    void    changeGun(Gun * gun);
    void    fire(Touch * touch,Event * event);
    void    stop();
    
    void    reloadCall();
    void    shootCall();
    void    changeCall();
    
    bool    isWait();
    bool    isRun();
    bool    isReload();
    bool    isShoot();
    bool    isChange();
public:
    Human();
    ~Human();
    static Human * getInstance();
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__Human__) */
