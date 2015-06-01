//
//  HumanWaitState.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/16.
//
//

#include "HumanWaitState.h"
#include "HumanShootState.h"
#include "HumanReloadState.h"


HumanWaitState * HumanWaitState::getInstance()
{
    static HumanWaitState state;
    return &state;
}
void HumanWaitState::Enter(Human * human)
{
    human->setStateWait();
}
void HumanWaitState::Execute(Human * human)
{
    if (human->getWaitingTime() > 0.0f) {
        human->minusWaitingTime();
    }else if (human->isTouching())
    {
        human->changeState(HumanShootState::getInstance());
    }else if (!human->isFull())
    {
        if (dlay >= 1)
        {
            human->changeState(HumanReloadState::getInstance());
            dlay = 0;
        }else
        {
            dlay += 0.055;
        }
        
    }
}
void HumanWaitState::Exit(Human * human)
{
    
}
