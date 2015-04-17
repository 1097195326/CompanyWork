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
    if (human->isTouching())
    {
        human->changeState(HumanShootState::getInstance());
    }else if (!human->isFull())
    {
        human->changeState(HumanReloadState::getInstance());
    }
}
void HumanWaitState::Exit(Human * human)
{
    
}
