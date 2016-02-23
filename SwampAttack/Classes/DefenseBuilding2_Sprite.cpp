//
//  DefenseBuilding2_Sprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/19.
//
//

#include "DefenseBuilding2_Sprite.h"
#include "GameFightScene.h"
#include "BaseUtil.h"


DefenseBuilding2_Sprite::DefenseBuilding2_Sprite(DefenseBuilding * building):
DefenseBuildingSprite(building)
{
    m_buildingS = Sprite::create();
    addChild(m_buildingS);
    m_buildingS->setPosition(_G_M_M->fightScene_zhalan_point);
    
    
    attackAction = RepeatForever::create(Spawn::create(FadeIn::create(0.3),
                                                    Sequence::create(DelayTime::create(0.08 * 3),
                                                                     CallFunc::create(CC_CALLBACK_0(DefenseBuilding2_Sprite::attackCall, this)), NULL),
                                                    Sequence::create(BaseUtil::makeAnimateWithNameAndIndex("building2", 6),
                                                                     CallFunc::create(CC_CALLBACK_0(DefenseBuilding2_Sprite::palyEndCall, this)),NULL),
                                                    NULL));
    attackAction->retain();
    waitAction = Sequence::create(FadeOut::create(0.3),NULL);
    waitAction->retain();
    _G_V->addChild(this,3);
    scheduleUpdate();
}
DefenseBuilding2_Sprite::~DefenseBuilding2_Sprite()
{
    attackAction->release();
    waitAction->release();
}
void DefenseBuilding2_Sprite::update(float data)
{
    if (m_building->isStateWait()) {
        waitPlay();
    }else if (m_building->isStateHurting())
    {
        attackPlay();
    }
}
void DefenseBuilding2_Sprite::attackPlay()
{
    if (m_state == d2_hurting) {
        return;
    }
    m_state = d2_hurting;
    m_buildingS->stopAllActions();
    m_buildingS->runAction(attackAction);
}
void DefenseBuilding2_Sprite::waitPlay()
{
    if (m_state == d2_wait) {
        return;
    }
    m_state = d2_wait;
    m_buildingS->stopAllActions();
    m_buildingS->runAction(waitAction);
}
void DefenseBuilding2_Sprite::attackCall()
{
    m_building->hurtCall();
}
void DefenseBuilding2_Sprite::palyEndCall()
{
    //    m_building->setStateWait();
}