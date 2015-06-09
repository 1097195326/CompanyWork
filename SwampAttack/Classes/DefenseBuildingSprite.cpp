//
//  DefenseBuildingSprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/20.
//
//

#include "DefenseBuildingSprite.h"
#include "GameFightScene.h"


DefenseBuildingSprite::DefenseBuildingSprite(DefenseBuilding * building):
m_building(building)
{
    init();
    _G_V->addChild(this,3);
}