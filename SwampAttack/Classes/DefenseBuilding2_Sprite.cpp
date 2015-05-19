//
//  DefenseBuilding2_Sprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/19.
//
//

#include "DefenseBuilding2_Sprite.h"


bool DefenseBuilding2_Sprite::init()
{
    if (!Sprite::init()) {
        return false;
    }
    
    Sprite * building = Sprite::create(ImagePath("fight_building2.png"));
    addChild(building);
    building->setPosition(visibleOrigin.x + 320,visibleOrigin.y + 100);
    
    scheduleUpdate();
    return true;
}
void DefenseBuilding2_Sprite::setModel(DefenseBuilding *building)
{
    m_building = building;
}
void DefenseBuilding2_Sprite::update(float data)
{
    
}