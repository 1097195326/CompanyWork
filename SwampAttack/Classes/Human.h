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
#include "PropManager.h"

enum HumanStatus
{
    _h_normal = 1,
    _h_waits,
    _h_run,
    _h_reloading,
    _h_reloaded,
    _h_shooting,
    _h_shooted,
    _h_changeing,
    _h_changed,
    _h_throwing,
    _h_throwed,
    
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
    std::queue<Prop *> m_throwPropStack;
    
    Vec2    m_fireToPoint;
    float   m_waitingTime;
private:
    
    
public:
    //--- interface for game director
    void    changeState(State<Human> * state);
    void    changeGun(Gun * gun);
    Gun *   getGun();
    void    throwProp(Prop * prop);
    void    fire(Touch * touch,Event * event);
    void    stop();
    void    resetData();
    
    //--- interface for view call back
    void    reloadCall();
    void    shootCall();
    void    changeCall();
    void    throwPropCall();
    
    //--- interface for state
    void    setStateShoot();
    void    setStateReload();
    void    setStateWait();
    void    setStateChange();
    void    setStateThrow();
    
    float   getWaitingTime();
    void    minusWaitingTime();
    
    bool    isTouching();
    bool    isTouchEnd();
    bool    isFull();
    bool    isHaveBullet();
    bool    isReloaded();
    bool    isShooted();
    bool    isChanged();
    bool    isThrowEnd();
    //--- interface for view
    Vec2    getPosition();
    bool    isWait();
    bool    isRun();
    bool    isReload();
    bool    isShoot();
    bool    isChange();
    bool    isThrowing();
public:
    Human();
    ~Human();
    static Human * getInstance();
    void    gameLoop(float data);
    void    setView();
};

#endif /* defined(__SwampAttack__Human__) */
