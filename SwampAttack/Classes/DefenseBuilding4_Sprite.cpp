//
//  DefenseBuilding4_Sprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/19.
//
//

#include "DefenseBuilding4_Sprite.h"
#include "GameFightScene.h"
#include "BaseUtil.h"


DefenseBuilding4_Sprite::DefenseBuilding4_Sprite(DefenseBuilding * building):
DefenseBuildingSprite(building)
{
    
    
    
    Vec2 point = _G_M_M->fightScene_tengman_point;
    int num = m_building->getNumber();
    for (int i = 0; i < num; ++i)
    {
        Action * attackAction = Sequence::create(Spawn::create(FadeIn::create(0.3),
                                                      Sequence::create(BaseUtil::makeAnimateWithNameAndIndex("building4", 10),
                                                                       CallFunc::create(CC_CALLBACK_0(DefenseBuilding4_Sprite::palyEndCall, this)),NULL),
                                                      NULL),
                                        NULL);
        attackAction->retain();
        m_attackActions.push_back(attackAction);
        
        Action * waitAction = Sequence::create(FadeOut::create(0.3),NULL);
        waitAction->retain();
        m_waitActions.push_back(waitAction);
        
        Sprite * building = Sprite::create();
        addChild(building);
        building->setPosition(point + Vec2(180 * (i - 1), 0));
        m_buildingS.push_back(building);
    }
    
    _G_V->addChild(this,2);
    scheduleUpdate();
}
DefenseBuilding4_Sprite::~DefenseBuilding4_Sprite()
{
    for (auto iter = m_attackActions.begin(); iter != m_attackActions.end(); ++iter) {
        (*iter)->release();
    }
    
    for (auto iter = m_waitActions.begin(); iter != m_waitActions.end(); ++iter) {
        (*iter)->release();
    }
    
}
void DefenseBuilding4_Sprite::update(float data)
{
    if (m_building->isStateWait()) {
        waitPlay();
    }else if (m_building->isStateHurting())
    {
        attackPlay();
    }
}
void DefenseBuilding4_Sprite::attackPlay()
{
    if (m_state == d4_hurting) {
        return;
    }
    m_state = d4_hurting;
    playIndex = 0;
    m_buildingS[playIndex]->stopAllActions();
    m_buildingS[playIndex]->runAction(m_attackActions[playIndex]);
}
void DefenseBuilding4_Sprite::waitPlay()
{
    if (m_state == d4_wait) {
        return;
    }
    m_state = d4_wait;
    int num = m_building->getNumber();
    for (int i = 0; i < num; ++i)
    {
        m_buildingS[i]->runAction(m_waitActions[i]);
    }
    
}
void DefenseBuilding4_Sprite::attackCall()
{
    
}
void DefenseBuilding4_Sprite::palyEndCall()
{
    m_building->hurtCall();
    ++playIndex;
    if (playIndex < (int)m_buildingS.size())
    {
        m_buildingS[playIndex]->stopAllActions();
        m_buildingS[playIndex]->runAction(m_attackActions[playIndex]);
    }
    
}