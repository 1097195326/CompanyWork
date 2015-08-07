//
//  DefenseBuilding6_Sprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/8/7.
//
//

#ifndef __SwampAttack__DefenseBuilding6_Sprite__
#define __SwampAttack__DefenseBuilding6_Sprite__

#include "BaseCode.h"
#include "DefenseBuildingSprite.h"


class DefenseBuilding6_Sprite : public DefenseBuildingSprite {
private:
    
public:
    DefenseBuilding6_Sprite(DefenseBuilding * building);
    void    update(float data);
};

#endif /* defined(__SwampAttack__DefenseBuilding6_Sprite__) */
