//
//  HumanThrowPropState.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/3.
//
//

#include "HumanThrowPropState.h"
#include "HumanWaitState.h"

HumanThrowPropState * HumanThrowPropState::getInstance()
{
    static HumanThrowPropState state;
    return &state;
}
void HumanThrowPropState::Enter(Human * human)
{
    human->setStateThrow();
}
void HumanThrowPropState::Execute(Human * human)
{
    if (human->isThrowEnd())
    {
        human->changeState(HumanWaitState::getInstance());
    }
}
void HumanThrowPropState::Exit(Human * human)
{
    
}