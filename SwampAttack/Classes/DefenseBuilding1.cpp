//
//  DefenseBuilding1.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/8.
//
//

#include "DefenseBuilding1.h"
#include "DefenseBuilding1_Sprite.h"
#include "DefenseBuilding6_Sprite.h"
#include "DefenseBuilding7_Sprite.h"
#include "House.h"

DefenseBuilding1::DefenseBuilding1(Json::Value data):DefenseBuilding(data)
{
    
}
void DefenseBuilding1::setView()
{
    if (!m_isUnlock) {
        return;
    }
    House::getInstance()->addHealth(m_hp);
    
    if (m_modelId == "building1")
    {
        DefenseBuildingSprite * sprite = new DefenseBuilding1_Sprite(this);
        sprite->autorelease();
    }else if (m_modelId == "building6")
    {
        DefenseBuildingSprite * sprite = new DefenseBuilding6_Sprite(this);
        sprite->autorelease();
    }else if (m_modelId == "building7")
    {
        DefenseBuildingSprite * sprite = new DefenseBuilding7_Sprite(this);
        sprite->autorelease();
    }
    
    

}
