//
//  DefenseBuilding7_Sprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/8/7.
//
//

#ifndef __SwampAttack__DefenseBuilding7_Sprite__
#define __SwampAttack__DefenseBuilding7_Sprite__

#include "BaseCode.h"
#include "DefenseBuildingSprite.h"


class DefenseBuilding7_Sprite : public DefenseBuildingSprite {
private:
    
public:
    DefenseBuilding7_Sprite(DefenseBuilding * building);
    void    update(float data);
};

#endif /* defined(__SwampAttack__DefenseBuilding7_Sprite__) */
