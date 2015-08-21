//
//  DefenseBuilding.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/14.
//
//

#include "DefenseBuilding.h"
#include "ConfigManager.h"
#include "GameUser.h"
#include "GameDirector.h"
#include "House.h"
#include "BulletManager.h"

#include "GuanQiaManager.h"
#include "GameShowDiscLayer.h"


DefenseBuilding::DefenseBuilding(Json::Value data):
m_isMaxLevel(false),
m_isUnlock(false),
m_state(d_normal),
m_index(0.0)
{
    m_id = data["DefenceId"].asString() ;
    string defenceName = data["DefenceName"].asString();
    m_defenceName = _C_M->getTranslateById(defenceName);
    m_modelId = data["ModelId"].asString();
    m_bulletModelId = data["BulletModelId"].asString();
    m_defenceType = atoi(data["DefenceType"].asString().c_str());
    m_damageArea = atof(data["DamageArea"].asString().c_str());
    m_unlockMission = data["UnlockMission"].asString();
    m_unlockGold = atoi(data["UnlockGold"].asString().c_str());
    string defenceDescription = data["DefenceDescription"].asString();
    m_defenceDescription = _C_M->getTranslateById(defenceDescription);
    m_limitLevel = atoi(data["LimitLevel"].asString().c_str());
    //
    m_strengthenLevel = _G_U->getBuildingLevel(m_id);
    string upId = StringUtils::format("%s_%d",m_id.c_str(),m_strengthenLevel);
    Json::Value upgradeData = _C_M->getDataByTag("buildingUpgrade",upId);
    m_damage = atof(upgradeData["Damage"].asString().c_str());
    m_hp = atoi(upgradeData["Hp"].asString().c_str());
    m_deceleration = atof(upgradeData["Deceleration"].asString().c_str());
    if (m_limitLevel == m_strengthenLevel)
    {
        m_isMaxLevel = true;
    }else
    {
        m_strengthenGold = atoi(upgradeData["StrengthenGold"].asString().c_str());
    }
    
    m_isUnlock = _G_U->isUnlockBuilding(m_id);
    
}
DefenseBuilding::~DefenseBuilding()
{
    
}
void DefenseBuilding::gameLoop(float data)
{
}
void DefenseBuilding::setView()
{
    if (!m_isUnlock) {
        return;
    }
}
void DefenseBuilding::checkUnlock(Layer * layer)
{
    if (!(m_unlockMission.size() > 0)) {
        return;
    }
    GuanqiaModel * guanqia = GuanQiaManager::getInstance()->getGuanqiaById(m_unlockMission);
    if (guanqia && guanqia->isUnlock() && !m_isUnlock)
    {
        m_isUnlock = true;
        _G_U->unlockBuilding(m_id);
        
        GameShowDiscLayer * showLayer = new GameShowDiscLayer(m_modelId,
                                                              m_defenceDescription,
                                                              Vec2(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                                                                   m_visibleOrigin.y + m_visibleSize.height * 0.5),
                                                              true,
                                                              this,
                                                              1);
        showLayer->autorelease();
        layer->addChild(showLayer,201);
    }
}
void DefenseBuilding::addStrengthenLevel()
{
    m_strengthenLevel += 1;
    _G_U->setBuildingLevel(m_id, m_strengthenLevel);
    string upId = StringUtils::format("%s_%d",m_id.c_str(),m_strengthenLevel);
    Json::Value upgradeData = _C_M->getDataByTag("buildingUpgrade",upId);
    m_damage = atof(upgradeData["Damage"].asString().c_str());
    m_hp = atoi(upgradeData["Hp"].asString().c_str());
    if (m_limitLevel == m_strengthenLevel)
    {
        m_isMaxLevel = true;
    }else
    {
        m_strengthenGold = atoi(upgradeData["StrengthenGold"].asString().c_str());
    }
}
bool DefenseBuilding::isCanHurt()
{
    return m_state == d_canHurt;
}
bool DefenseBuilding::isStateHurting()
{
    return m_state == d_hurting;
}
bool DefenseBuilding::isStateWait()
{
    return m_state == d_wait;
}
void DefenseBuilding::setStateWait()
{
    m_state = d_wait;
}
void DefenseBuilding::hurtEnemy(Enemy * enemy)
{
    
}
void DefenseBuilding::hurtCall()
{
}
bool DefenseBuilding::isInRange(cocos2d::Vec2 point)
{
    switch (m_defenceType) {
        case 2:
            if (point.x < _G_M_M->fightScene_zhalan_line + m_damageArea)
            {
                return true;
            }
            break;
        case 3:
            if (point.x < _G_M_M->fightScene_gangpao_Point.x + m_damageArea)
            {
                return true;
            }
        case 4:
            if (point.x < _G_M_M->fightScene_tengman_point.x + m_damageArea)
            {
                return true;
            }
        default:
            break;
    }
    
    return false;
}
bool DefenseBuilding::isUnlock()
{
    return m_isUnlock;
}
void DefenseBuilding::unlockBuilding()
{
    m_isUnlock = true;
    _G_U->unlockBuilding(m_id);
}
bool DefenseBuilding::isMaxLevel()
{
    return m_isMaxLevel;
}
//--- get function ---
string DefenseBuilding::getId()
{
    return m_id;
}
string DefenseBuilding::getDefenceName()
{
    return m_defenceName;
}
string DefenseBuilding::getModelId()
{
    return m_modelId;
}
int DefenseBuilding::getDefenceType()
{
    return m_defenceType;
}
float DefenseBuilding::getDamageArea()
{
    return m_damageArea;
}
string DefenseBuilding::getUnlockMission()
{
    return m_unlockMission;
}
int DefenseBuilding::getUnlockGold()
{
    return m_unlockGold;
}
string DefenseBuilding::getDefenceDescription()
{
    return m_defenceDescription;
}
int DefenseBuilding::getLimitLevel()
{
    return m_limitLevel;
}
//
int DefenseBuilding::getStrengthLevel()
{
    return m_strengthenLevel;
}
int DefenseBuilding::getHp()
{
    return m_hp;
}
int DefenseBuilding::getDamage()
{
    return m_damage;
}
int DefenseBuilding::getStrengthGold()
{
    return m_strengthenGold;
}
