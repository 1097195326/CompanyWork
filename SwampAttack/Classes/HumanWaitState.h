//
//  HumanWaitState.h
//  SwampAttack
//
//  Created by oceantech02 on 15/4/16.
//
//

#ifndef __SwampAttack__HumanWaitState__
#define __SwampAttack__HumanWaitState__

#include "State.h"

class HumanWaitState : public State<Human *>
{
public:
    HumanWaitState();
    ~HumanWaitState();
    static HumanWaitState * getInstance();
    void Enter(Human *);
    void Execute(Human *);
    void Exit(Human *);
};

#endif /* defined(__SwampAttack__HumanWaitState__) */
