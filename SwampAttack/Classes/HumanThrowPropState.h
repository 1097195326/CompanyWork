//
//  HumanThrowPropState.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/3.
//
//

#ifndef __SwampAttack__HumanThrowPropState__
#define __SwampAttack__HumanThrowPropState__

#include "State.h"
#include "Human.h"

class HumanThrowPropState : public State<Human> {
    
public:
    static HumanThrowPropState * getInstance();
    void    Enter(Human *);
    void    Execute(Human *);
    void    Exit(Human *);
};


#endif /* defined(__SwampAttack__HumanThrowPropState__) */
