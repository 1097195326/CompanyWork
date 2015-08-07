//
//  DefenseBuilding6_Sprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/8/7.
//
//

#include "DefenseBuilding6_Sprite.h"
#include "GameFightScene.h"


DefenseBuilding6_Sprite::DefenseBuilding6_Sprite(DefenseBuilding * building):
DefenseBuildingSprite(building)
{
    Sprite * buildingS2 = Sprite::create(ImagePath("fight_building6_1.png"));
    addChild(buildingS2);
    buildingS2->setPosition(_G_M_M->fightScene_tieban_point1);
    Sprite * buildingS1 = Sprite::create(ImagePath("fight_building6_2.png"));
    addChild(buildingS1);
    buildingS1->setPosition(_G_M_M->fightScene_tieban_point2);
    
    _G_V->addChild(this,3);
}
void DefenseBuilding6_Sprite::update(float data)
{
    
}