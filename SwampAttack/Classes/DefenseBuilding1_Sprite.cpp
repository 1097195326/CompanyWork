//
//  DefenseBuilding1_Sprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/19.
//
//

#include "DefenseBuilding1_Sprite.h"
#include "GameFightScene.h"

DefenseBuilding1_Sprite::DefenseBuilding1_Sprite(DefenseBuilding * building):
DefenseBuildingSprite(building)
{
    
    string modelId = m_building->getModelId();
//    log("%s",modelId.c_str());
//    if (modelId == "building1")
    {
        
        Sprite * buildingS = Sprite::create(ImagePath("fight_building1.png"));
        addChild(buildingS);
        buildingS->setPosition(m_visibleOrigin.x + 20,m_visibleOrigin.y + 260);
        Sprite * buildingS2 = Sprite::create(ImagePath("fight_building1.png"));
        addChild(buildingS2);
        buildingS2->setPosition(m_visibleOrigin.x + 90,m_visibleOrigin.y + 260);
        _G_V->addChild(this,3);
    }
    
    
}