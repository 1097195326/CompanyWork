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
#include "Human.h"

class HumanWaitState : public State<Human>
{
private:
    float   dlay = 0.0f;
public:
    virtual void Enter(Human *);
    virtual void Execute(Human *);
    virtual void Exit(Human *);
    static HumanWaitState * getInstance();
};

#endif /* defined(__SwampAttack__HumanWaitState__) */
