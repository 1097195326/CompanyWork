//
//  HumanReloadState.h
//  SwampAttack
//
//  Created by oceantech02 on 15/4/16.
//
//

#ifndef __SwampAttack__HumanReloadState__
#define __SwampAttack__HumanReloadState__

#include "State.h"
#include "Human.h"

class HumanReloadState : public State<Human> {
    
public:
    static HumanReloadState * getInstance();
    void    Enter(Human *);
    void    Execute(Human *);
    void    Exit(Human *);
};

#endif /* defined(__SwampAttack__HumanReloadState__) */
