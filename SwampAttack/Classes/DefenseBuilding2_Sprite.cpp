//
//  DefenseBuilding2_Sprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/19.
//
//

#include "DefenseBuilding2_Sprite.h"


DefenseBuilding2_Sprite::DefenseBuilding2_Sprite(DefenseBuilding * building):
DefenseBuildingSprite(building)
{
    Sprite * buildingS2 = Sprite::create(ImagePath("fight_building2.png"));
    addChild(buildingS2);
    buildingS2->setPosition(_G_M_M->fightScene_zhalan_point2);
    Sprite * buildingS1 = Sprite::create(ImagePath("fight_building2.png"));
    addChild(buildingS1);
    buildingS1->setPosition(_G_M_M->fightScene_zhalan_point1);
    
    scheduleUpdate();
}
void DefenseBuilding2_Sprite::update(float data)
{
    
}