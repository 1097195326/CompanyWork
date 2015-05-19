//
//  DefenseBuilding4_Sprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/19.
//
//

#include "DefenseBuilding4_Sprite.h"

bool DefenseBuilding4_Sprite::init()
{
    if (!Sprite::init()) {
        return false;
    }
    Sprite * building = Sprite::create(ImagePath("fight_building4.png"));
    addChild(building);
    building->setPosition(visibleOrigin.x + 130,visibleOrigin.y + 320);
    
    
    return true;
}
void DefenseBuilding4_Sprite::setModel(DefenseBuilding *building)
{
    m_building = building;
}
void DefenseBuilding4_Sprite::update(float data)
{
    
}