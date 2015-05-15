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


DefenseBuilding::DefenseBuilding(Json::Value data):m_isMaxLevel(false),m_isUnlock(false)
{
    m_id = data["DefenceId"].asString() ;
    string defenceName = data["DefenceName"].asString();
    m_defenceName = _C_M->getTranslateById(defenceName);
    m_modelId = data["ModelId"].asString();
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
    if (m_limitLevel == m_strengthenLevel)
    {
        m_isMaxLevel = true;
    }else
    {
        m_strengthenGold = atoi(upgradeData["StrengthenGold"].asString().c_str());
    }
    
    m_isUnlock = _G_U->isUnlockGun(m_id);
    
}
DefenseBuilding::~DefenseBuilding()
{
    
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
