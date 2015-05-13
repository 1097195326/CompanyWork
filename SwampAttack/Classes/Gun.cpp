//
//  Gun.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/30.
//
//

#include "Gun.h"
#include "BulletManager.h"
#include "GameMapManager.h"
#include "ConfigManager.h"
#include "GameUser.h"


Gun::Gun(Json::Value data):m_isMaxLevel(false),m_isUnlock(false)
{
    
    m_id = data["Id"].asString() ;
    string weaponId = data["WeaponName"].asString();
    m_weaponName = _C_M->getTranslateById(weaponId);
    m_modelId = data["ModelId"].asString();
    m_bulletModelId = data["BulletModelId"].asString();
    m_underAttackAction = atoi(data["UnderAttackAction"].asString().c_str());
    m_weaponType = data["WeaponType"].asString();
    m_limitLevel = atoi(data["LimitLevel"].asString().c_str());
    m_damageArea = atof(data["DamageArea"].asString().c_str());
    m_shrapnelNumber = atoi(data["ShrapnelNumber"].asString().c_str());
    m_critRate = atof(data["CritRate"].asString().c_str());
    m_critDamageRate = atof(data["CritDamageRate"].asString().c_str());
    m_accuracy = atof(data["Accuracy"].asString().c_str());
    m_fireRate = atof(data["FireRate"].asString().c_str());
    m_range = atof(data["Range"].asString().c_str());
    m_bulletSpeed = atof(data["BulletSpeed"].asString().c_str());
    m_reloadType = atoi(data["ReloadType"].asString().c_str());
    m_reloadSpeed = atof(data["ReloadSpeed"].asString().c_str());
    m_switchSpeed = atof(data["SwitchSpeed"].asString().c_str());
    m_ammunltionLimit = atoi(data["AmmunitionLimit"].asString().c_str());
    m_magazieSize = atoi(data["MagazineSize"].asString().c_str());
    m_bulletPrice = atoi(data["BulletPrice"].asString().c_str());
    
    m_unlockMission = data["UnlockMission"].asString();
    m_unlockGold = atoi(data["UnlockGold"].asString().c_str());
    
    m_weaponDescription = data["WeaponDescription"].asString();// _C_M->getTranslateById( data["WeaponDescription"].asString());
    //-------
    m_bullets = _G_U->getGunBulletNumber(m_id);
    m_strengthenLevel = _G_U->getGunLevel(m_id);
    string upId = StringUtils::format("%s_%d",m_id.c_str(),m_strengthenLevel);
    Json::Value upgradeData = _C_M->getDataByTag("wuqiUpgrade",upId);
    m_damage = atof(upgradeData["Damage"].asString().c_str());
    if (m_limitLevel == m_strengthenLevel)
    {
        m_isMaxLevel = true;
    }else
    {
        m_strengthenGold = atoi(upgradeData["StrengthenGold"].asString().c_str());
    }
    
    m_isUnlock = _G_U->isUnlockGun(m_id);
    
}
Gun::~Gun()
{
    
}
void Gun::gameLoop(float data)
{
    
}
void Gun::fire(Vec2 position)
{
    --m_bullets;
    GameMap * map = GameMapManager::getInstance()->getGameMap();
    
    BulletParameter bp(m_damage,
                       m_damageArea,
                       m_shrapnelNumber,
                       m_critRate,
                       m_critDamageRate,
                       m_accuracy,
                       m_range,
                       m_bulletSpeed,
                       t_enemy,
                       map->m_BulletStartPoint,
                       position
                       );
    BulletManager::getInstance()->fire(bp);
    
}
void Gun::reloadBullet()
{
    ++m_bullets;
}
bool Gun::isUnlock()
{
    return m_isUnlock;
}
void Gun::unlockGun()
{
    m_isUnlock = true;
    _G_U->unlockGun(m_id);
}
bool Gun::isMaxLevel()
{
    return m_isMaxLevel;
}
bool Gun::isFull()
{
    return m_bullets == m_magazieSize;
}
bool Gun::isHaveBullet()
{
    return m_bullets > 0;
}
void Gun::addStrengthenLevel()
{
    m_strengthenLevel += 1;
    _G_U->setGunLevel(m_id, m_strengthenLevel);
    string upId = StringUtils::format("%s_%d",m_id.c_str(),m_strengthenLevel);
    Json::Value upgradeData = _C_M->getDataByTag("wuqiUpgrade",upId);
    m_damage = atof(upgradeData["Damage"].asString().c_str());
    if (m_limitLevel == m_strengthenLevel)
    {
        m_isMaxLevel = true;
    }else
    {
        m_strengthenGold = atoi(upgradeData["StrengthenGold"].asString().c_str());
    }
}
void Gun::buyBullet()
{
    m_bullets += m_magazieSize;
    _G_U->setGunBulletNumber(m_id, m_bullets);
    int userGold = _G_U->getUserGold();
    userGold -= m_bulletPrice;
    _G_U->setUserGold(userGold);
}
int Gun::getBulletNum()
{
    return m_bullets;
}
string Gun::getWeaponName()
{
    return m_weaponName;
}
string Gun::getModelId()
{
    return m_modelId;
}
string Gun::getBulletModelId()
{
    return m_bulletModelId;
}
int Gun::getUnderAttackAction()
{
    return m_underAttackAction;
}
int Gun::getLimitLevel()
{
    return m_limitLevel;
}
int Gun::getStrengthenLevel()
{
    return m_strengthenLevel;
}
int Gun::getStrengthenGold()
{
    return m_strengthenGold;
}
float Gun::getDamage()
{
    return m_damage;
}
float Gun::getDamageArea()
{
    return m_damageArea;
}
int Gun::getShrapnelNumber()
{
    return m_shrapnelNumber;
}
float Gun::getCritRate()
{
    return m_critRate;
}
float Gun::getCritDamageRate()
{
    return m_critDamageRate;
}
float Gun::getAccuracy()
{
    return m_accuracy;
}
float Gun::getFireRate()
{
    return m_fireRate;
}
float Gun::getRange()
{
    return m_range;
}
float Gun::getBulletSpeed()
{
    return m_bulletSpeed;
}
int Gun::getReloadType()
{
    return m_reloadType;
}
float Gun::getReloadSpeed()
{
    return m_reloadSpeed;
}
float Gun::getSwitchSpeed()
{
    return m_switchSpeed;
}
int Gun::getAmmunltionLimit()
{
    return m_ammunltionLimit;
}
int Gun::getMagazieSize()
{
    return m_magazieSize;
}
int Gun::getBulletPrice()
{
    return m_bulletPrice;
}
string Gun::getUnlockMission()
{
    return m_unlockMission;
}
int Gun::getUnlockGold()
{
    return m_unlockGold;
}
string Gun::getWeaponDescription()
{
    return m_weaponDescription;
}

