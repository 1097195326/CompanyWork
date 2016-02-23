//
//  DefenseBuilding3.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/8.
//
//

#ifndef __SwampAttack__DefenseBuilding3__
#define __SwampAttack__DefenseBuilding3__

#include "DefenseBuilding.h"


class DefenseBuilding3 : public DefenseBuilding {
private:
    Enemy * fireEnemy;
    bool    canfire;
    int     numberIndex;
public:
    DefenseBuilding3(Json::Value data);
    void    setView();
    
    void    setStateCanhurt();
    void    setStateHurting();
    
    void    hurtEnemy(Enemy * enemy);
    void    hurtCall();
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__DefenseBuilding3__) */
