//
//  DefenseBuildingSprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/20.
//
//

#ifndef __SwampAttack__DefenseBuildingSprite__
#define __SwampAttack__DefenseBuildingSprite__

#include "BaseCode.h"
#include "DefenseBuilding.h"
#include "GameMapManager.h"



class DefenseBuildingSprite : public Sprite {
protected:
    DefenseBuilding * m_building;
public:
    DefenseBuildingSprite(DefenseBuilding * building);
    
};

#endif /* defined(__SwampAttack__DefenseBuildingSprite__) */
