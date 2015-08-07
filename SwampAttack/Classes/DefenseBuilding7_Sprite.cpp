//
//  DefenseBuilding7_Sprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/8/7.
//
//

#include "DefenseBuilding7_Sprite.h"
#include "GameFightScene.h"


DefenseBuilding7_Sprite::DefenseBuilding7_Sprite(DefenseBuilding * building):
DefenseBuildingSprite(building)
{
    Sprite * buildingS2 = Sprite::create(ImagePath("fight_building7.png"));
    addChild(buildingS2);
    buildingS2->setPosition(_G_M_M->fightScene_shadai_point);
    
    _G_V->addChild(this,3);
}
void DefenseBuilding7_Sprite::update(float data)
{
    
}