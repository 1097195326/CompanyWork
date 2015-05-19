//
//  DefenseBuilding1_Sprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/19.
//
//

#include "DefenseBuilding1_Sprite.h"

bool DefenseBuilding1_Sprite::init()
{
    if (!Sprite::init()) {
        return false;
    }
    Sprite * building = Sprite::create(ImagePath("fight_building1.png"));
    addChild(building);
    building->setPosition(visibleOrigin.x,visibleOrigin.y + 220);
    Sprite * building2 = Sprite::create(ImagePath("fight_building1.png"));
    addChild(building2);
    building2->setPosition(visibleOrigin.x + 70,visibleOrigin.y + 220);
    
    return true;
}