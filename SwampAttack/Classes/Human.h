//
//  Human.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#ifndef __SwampAttack__Human__
#define __SwampAttack__Human__

#include "GameObject.h"

enum HumanStatus
{
    waits   = 0b00000001,
    run     = 0b00000010,
    reload  = 0b00000100,
    shoot   = 0b00001000,
    exch    = 0b00010000,
    
};

class Human : public GameObject {
private:
    HumanStatus m_status;
    
public:
    Human();
    ~Human();
    
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__Human__) */
