//
//  House.h
//  SwampAttack
//
//  Created by oceantech02 on 15/4/13.
//
//

#ifndef __SwampAttack__House__
#define __SwampAttack__House__

#include "BaseCode.h"

enum HouseState
{
    _h_normal    = 0b00000000,
    
};
class House {
private:
    float   health;
    
private:
    House();
    ~House();
public:
    static House * getInstance();
    void    hurt(float damage);
    
};

#endif /* defined(__SwampAttack__House__) */
