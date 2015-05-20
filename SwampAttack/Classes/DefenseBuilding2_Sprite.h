//
//  DefenseBuilding2_Sprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/19.
//
//

#ifndef __SwampAttack__DefenseBuilding2_Sprite__
#define __SwampAttack__DefenseBuilding2_Sprite__

#include "BaseCode.h"
#include "DefenseBuildingSprite.h"


class DefenseBuilding2_Sprite : public DefenseBuildingSprite {
private:
    
public:
    DefenseBuilding2_Sprite(DefenseBuilding * building);
    void update(float data);
};

#endif /* defined(__SwampAttack__DefenseBuilding2_Sprite__) */
