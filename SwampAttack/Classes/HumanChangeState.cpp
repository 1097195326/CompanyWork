//
//  HumanChangeState.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/25.
//
//

#include "HumanChangeState.h"
#include "HumanWaitState.h"

HumanChangeState * HumanChangeState::getInstance()
{
    static HumanChangeState state;
    return &state;
}
void HumanChangeState::Enter(Human * human)
{
    human->setStateChange();
}
void HumanChangeState::Execute(Human * human)
{
    if (human->isChanged())
    {
        human->changeState(HumanWaitState::getInstance());
    }
}
void HumanChangeState::Exit(Human * human)
{
    
}