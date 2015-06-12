//
//  HumanShootState.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/16.
//
//

#include "HumanShootState.h"
#include "HumanReloadState.h"
#include "HumanWaitState.h"


HumanShootState * HumanShootState::getInstance()
{
    static HumanShootState state;
    return &state;
}
void HumanShootState::Enter(Human * human)
{
     human->setStateShoot();
}
void HumanShootState::Execute(Human * human)
{
    if (human->getWaitingTime() > 0.0f)
    {
        human->changeState(HumanWaitState::getInstance());
    }else if (human->isTouching())
    {
//        if (human->isShooted())
//        {
            if (human->isHaveBullet())
            {
                human->setStateShoot();
            }else
            {
                human->changeState(HumanReloadState::getInstance());
            }
//        }
    }else if (human->isTouchEnd() && human->isShooted())
    {
        human->changeState(HumanWaitState::getInstance());
    }
}
void HumanShootState::Exit(Human * human)
{
    
}