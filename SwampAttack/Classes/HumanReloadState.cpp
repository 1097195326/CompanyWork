//
//  HumanReloadState.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/16.
//
//

#include "HumanReloadState.h"
#include "HumanShootState.h"
#include "HumanWaitState.h"

HumanReloadState * HumanReloadState::getInstance()
{
    static HumanReloadState state;
    return &state;
}
void HumanReloadState::Enter(Human * human)
{
    human->setStateReload();
}
void HumanReloadState::Execute(Human * human)
{
    if (human->getWaitingTime() > 0.0f)
    {
        human->changeState(HumanWaitState::getInstance());
    }else if (human->isTouching() && human->isHaveBullet())
    {
        human->changeState(HumanShootState::getInstance());
    }else if (human->isTouchEnd())
    {
        if (human->isFull())
        {
            human->changeState(HumanWaitState::getInstance());
        }
    }
}
void HumanReloadState::Exit(Human * human)
{
    
}