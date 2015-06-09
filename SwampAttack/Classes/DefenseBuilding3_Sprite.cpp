//
//  DefenseBuilding3_Sprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/19.
//
//

#include "DefenseBuilding3_Sprite.h"
#include "BaseUtil.h"
#include "GameMapManager.h"


DefenseBuilding3_Sprite::DefenseBuilding3_Sprite(DefenseBuilding * building):
DefenseBuildingSprite(building)
{
    
    m_buildingS = Sprite::create();
    addChild(m_buildingS);
    m_buildingS->setPosition(_G_M_M->fightScene_gangpao_Point);
    
    attackAction = Sequence::create(
                                  Spawn::create(
                                                Sequence::create(DelayTime::create(0.08 * 3),
                                                                 CallFunc::create(CC_CALLBACK_0(DefenseBuilding3_Sprite::attackCall, this)), NULL),
                                                Sequence::create(BaseUtil::makeAnimateWithNameAndIndex("monkey_shoot", 7),CallFunc::create(CC_CALLBACK_0(DefenseBuilding3_Sprite::palyEndCall, this)),NULL),
                                                NULL),NULL);
    attackAction->retain();
    
    waitAction = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex("monkey_wait" ,7));
    waitAction->retain();
    
    scheduleUpdate();
}
DefenseBuilding3_Sprite::~DefenseBuilding3_Sprite()
{
    waitAction->release();
    attackAction->release();
    
}
void DefenseBuilding3_Sprite::update(float data)
{
    if (m_building->isStateWait()) {
        waitPlay();
    }else if (m_building->isStateHurting())
    {
        attackPlay();
    }
}
void DefenseBuilding3_Sprite::attackPlay()
{
    if (m_state == d3_hurting) {
        return;
    }
    m_state = d3_hurting;
    m_buildingS->stopAllActions();
    m_buildingS->runAction(attackAction);
}
void DefenseBuilding3_Sprite::waitPlay()
{
    if (m_state == d3_wait) {
        return;
    }
    m_state = d3_wait;
    m_buildingS->stopAllActions();
    m_buildingS->runAction(waitAction);
}
void DefenseBuilding3_Sprite::attackCall()
{
    m_building->hurtCall();
}
void DefenseBuilding3_Sprite::palyEndCall()
{
    m_building->setStateWait();
}