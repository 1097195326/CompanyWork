//
//  DefenseBuilding4.h
//  SwampAttack
//
//  Created by oceantech02 on 15/8/7.
//
//

#ifndef __SwampAttack__DefenseBuilding4__
#define __SwampAttack__DefenseBuilding4__

#include "DefenseBuilding.h"


class DefenseBuilding4 : public DefenseBuilding {
private:
    
public:
    DefenseBuilding4(Json::Value data);
    void    setView();
    void    hurtEnemy(Enemy * enemy);
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__DefenseBuilding4__) */
