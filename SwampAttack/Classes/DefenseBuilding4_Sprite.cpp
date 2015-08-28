//
//  DefenseBuilding4_Sprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/19.
//
//

#include "DefenseBuilding4_Sprite.h"
#include "GameFightScene.h"

DefenseBuilding4_Sprite::DefenseBuilding4_Sprite(DefenseBuilding * building):
DefenseBuildingSprite(building)
{
    
    Sprite * buildingS2 = Sprite::create(ImagePath("fight_building4.png"));
    addChild(buildingS2);
    buildingS2->setPosition(_G_M_M->fightScene_tengman_point);
    
    _G_V->addChild(this);
}
void DefenseBuilding4_Sprite::update(float data)
{
    
}