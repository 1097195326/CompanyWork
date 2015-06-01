//
//  HumanShootState.h
//  SwampAttack
//
//  Created by oceantech02 on 15/4/16.
//
//

#ifndef __SwampAttack__HumanShootState__
#define __SwampAttack__HumanShootState__

#include "State.h"
#include "Human.h"

class HumanShootState : public State<Human>
{
private:
    
public:
    static HumanShootState * getInstance();
    void Enter(Human *);
    void Execute(Human *);
    void Exit(Human *);
    void resetData();
};

#endif /* defined(__SwampAttack__HumanShootState__) */
