//
//  HumanChangeState.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/25.
//
//

#ifndef __SwampAttack__HumanChangeState__
#define __SwampAttack__HumanChangeState__

#include "State.h"
#include "Human.h"

class HumanChangeState : public State<Human> {
    
public:
    static HumanChangeState * getInstance();
    void    Enter(Human *);
    void    Execute(Human *);
    void    Exit(Human *);
};


#endif /* defined(__SwampAttack__HumanChangeState__) */
