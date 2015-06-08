//
//  DefenseBuilding2.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/8.
//
//

#ifndef __SwampAttack__DefenseBuilding2__
#define __SwampAttack__DefenseBuilding2__

#include "DefenseBuilding.h"


class DefenseBuilding2 : public DefenseBuilding {
private:
    
public:
    DefenseBuilding2(Json::Value data);
    void    setView();
    void    hurtEnemy(Enemy * enemy);
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__DefenseBuilding2__) */
