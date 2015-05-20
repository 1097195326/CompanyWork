//
//  DefenseBuilding3_Sprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/19.
//
//

#ifndef __SwampAttack__DefenseBuilding3_Sprite__
#define __SwampAttack__DefenseBuilding3_Sprite__

#include "BaseCode.h"
#include "DefenseBuildingSprite.h"


class DefenseBuilding3_Sprite : public DefenseBuildingSprite {
private:
    
public:
    DefenseBuilding3_Sprite(DefenseBuilding * building);
    void    update(float data);
    
};

#endif /* defined(__SwampAttack__DefenseBuilding3_Sprite__) */
