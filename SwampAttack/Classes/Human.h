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
#include "State.h"
#include "GameSubject.h"


enum HumanStatus
{
    _h_normal = 1,
    _h_waits,
    _h_run,
    _h_reloading,
//    _h_reloaded,
    _h_shooting,
    _h_shooted,
    _h_changeing,
    _h_changed
    
};
enum TouchStatus
{
    _t_normal,
    _isTouching,
    _touchEnd,
};
class Human : public GameObject ,public GameSubject {
private:
    int     m_status;
    TouchStatus m_touchStatus;
    State<Human> * m_state;
    
    Vec2    m_point;
    Gun *   m_gun;
    
    Vec2    m_fireToPoint;
private:
    void    setView();
    
public:
    //--- interface for game director
    void    changeState(State<Human> * state);
    void    changeGun(Gun * gun);
    Gun *   getGun();
    void    fire(Touch * touch,Event * event);
    void    stop();
    
    
    //--- interface for view call back
    void    reloadCall();
    void    shootCall();
    void    changeCall();
    
    //--- interface for state
    void    setStateShoot();
    void    setStateReload();
    void    setStateWait();
    
    bool    isTouching();
    bool    isTouchEnd();
    bool    isFull();
    bool    isHaveBullet();
//    bool    isReloaded();
    bool    isShooted();
    //--- interface for view
    Vec2    getPosition();
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
