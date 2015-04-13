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



class HumanSprite : public Sprite {
private:
    Human * human;
    std::map<std::string, Action *> m_actionData;
    
    
private:
    void    run();
    void    wait();
    void    shoot();
    void    reload();
    
    void    reloadShotCall();
    void    runShotCall();
    void    shootShotCall();
    void    waitShotCall();
    
public:
    HumanSprite();
    ~HumanSprite();
    CREATE_FUNC(HumanSprite);
    bool    init();
    
public:
    void    setModel(Human * human);
    
    void    update(float data);
};

#endif /* defined(__SwampAttack__HumanSprite__) */
