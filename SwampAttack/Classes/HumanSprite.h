//
//  HumanSprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/27.
//
//

#ifndef __SwampAttack__HumanSprite__
#define __SwampAttack__HumanSprite__

#include "BaseCode.h"
#include "Human.h"


enum H_ActionStatus
{
    _normal,
    _isReloading,
    _isRuning,
    _isShooting,
    _isWaiting,
    _isChangeing,
    _isThrowProp,
};
#include "GameObserver.h"

class HumanSprite : public Sprite {
private:
    Human * m_human;
    H_ActionStatus  m_status;
    std::map<std::string, Action *> m_actionData;
    
    
private:
    void    run();
    void    wait();
    void    shoot();
    void    reload();
    void    change();
    void    throwProp();
    void    changeActions();
    
    void    reloadShotCall();
    void    runShotCall();
    void    shootShotCall();
    void    waitShotCall();
    void    changeCall();
    void    throwEndCall();
    
public:
    HumanSprite();
    ~HumanSprite();
    CREATE_FUNC(HumanSprite);
public:
    void    setModel(Human * human);
    
    void    update(float data);
};

#endif /* defined(__SwampAttack__HumanSprite__) */
