//
//  DefenseBuilding3_Sprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/19.
//
//

#include "DefenseBuilding3_Sprite.h"

DefenseBuilding3_Sprite::DefenseBuilding3_Sprite(DefenseBuilding * building):
DefenseBuildingSprite(building)
{
    
    Sprite * buildingS = Sprite::create(ImagePath("fight_building4.png"));
    addChild(buildingS);
    buildingS->setPosition(m_visibleOrigin.x + 130,m_visibleOrigin.y + 320);
    
    scheduleUpdate();
}

void DefenseBuilding3_Sprite::update(float data)
{
    
}