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
#include "GunSprite.h"
#include "GameDirector.h"


GunActionInfo::GunActionInfo()
{
    GunActionData qiang3;
    qiang3.attackFrame = 3;
    qiang3.attackFrames = 5;
    qiang3.changeFrames = 9;
    qiang3.reloadFrames = 9;
    qiang3.waitFrames = 10;
    m_infoData["qiang3"] = qiang3;
    
    GunActionData qiang5;
    qiang5.attackFrame = 2;
    qiang5.attackFrames = 3;
    qiang5.changeFrames = 11;
    qiang5.reloadFrames = 11;
    qiang5.waitFrames = 10;
    m_infoData["qiang5"] = qiang5;
    
    GunActionData qiang7;
    qiang7.attackFrame = 2;
    qiang7.attackFrames = 3;
    qiang7.changeFrames = 11;
    qiang7.reloadFrames = 11;
    qiang7.waitFrames = 10;
    m_infoData["qiang7"] = qiang7;
    
}
GunActionInfo * GunActionInfo::getInstance()
{
    static GunActionInfo gunInfo;
    return &gunInfo;
}
GunActionData GunActionInfo::getInfoByName(string name)
{
    return m_infoData[name];
}
//----------
Gun::Gun(Json::Value data):
m_isMaxLevel(false),
m_isUnlock(false),
m_isTakeUp(false),
m_isDefaultGun(false),
m_isCurrentGun(false)
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
    //--- gun info
    GunActionData actionData = GunActionInfo::getInstance()->getInfoByName(m_modelId);
    m_fireRate =  1.0f/ m_fireRate / (float)actionData.attackFrames;
    m_reloadSpeed =  1.0f/ m_reloadSpeed / (float)actionData.reloadFrames;
    m_switchSpeed =  1.0f/ m_switchSpeed / (float)actionData.changeFrames;
    
    //-------
    m_totalBullets = _G_U->getGunBulletNumber(m_id);
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
    
    
    m_totalBullets = 200;
    
    if (m_id == defaultGunID) {
        m_bullets = m_magazieSize;
        m_isDefaultGun = true;
        m_isCurrentGun = true;
        m_isUnlock = true;
        m_isTakeUp = true;
        m_takeUpIndex = 1;
    }else
    {
        m_bullets = m_totalBullets >= m_magazieSize ? m_magazieSize : m_totalBullets % m_magazieSize;
        m_isUnlock = _G_U->isUnlockGun(m_id);
        m_isTakeUp = _G_U->isTakeUp(m_id);
        m_takeUpIndex = _G_U->getTakeUpIndex(m_id);
    }
    ///--- for test ---
    static int index = 1;
    m_isTakeUp = true;
    m_takeUpIndex = index;
    ++index;
    
}
Gun::~Gun()
{
    
}
bool Gun::fire(Vec2 position)
{
    --m_bullets;
    if (!m_isDefaultGun) {
        --m_totalBullets;
    }
    
    GameMap * map = GameMapManager::getInstance()->getGameMap();
    
    BulletParameter bp(m_damage,
                       m_damageArea,
                       m_shrapnelNumber,
                       m_critRate,
                       m_critDamageRate,
                       m_accuracy,
                       m_range,
                       m_bulletSpeed,
                       m_underAttackAction,
                       t_enemy,
                       map->m_BulletStartPoint,
                       position
                       );
    BulletManager::getInstance()->fire(bp);
    
    notify();
    if (m_isDefaultGun) {
        return true;
    }
    return m_totalBullets > 0;
}
void Gun::setFightView()
{
    GunSprite * sprite = new GunSprite(this);
    sprite->setSubject(this);
    sprite->autorelease();
    
}
void Gun::setShopView()
{
    
}
void Gun::reloadBullet()
{
    switch (m_reloadType) {
        case 1:
             ++m_bullets;
            if (!m_isDefaultGun) {
                m_bullets = m_bullets > m_totalBullets ? m_totalBullets : m_bullets;
            }
            break;
        case 2:
            if (m_isDefaultGun) {
                m_bullets = m_magazieSize;
            }else
            {
                m_bullets = m_totalBullets > m_magazieSize ? m_magazieSize : m_totalBullets % m_magazieSize;
            }
            break;
            
        default:
            break;
    }
    notify();
}
void Gun::takeUp(int index)
{
    m_isTakeUp = true;
    m_takeUpIndex = index;
    _G_U->setTakeUpGun(m_id, m_isTakeUp);
    _G_U->setTakeUpIndex(m_id, index);
}
void Gun::takeDown()
{
    m_isTakeUp = false;
    m_takeUpIndex = 0;
    _G_U->setTakeUpGun(m_id, m_isTakeUp);
    _G_U->setTakeUpIndex(m_id, 0);
}
void Gun::setIsCurrentGun(bool is)
{
    m_isCurrentGun = is;
}
bool Gun::isTakeUp()
{
    return m_isTakeUp;
}
int Gun::getTakeUpIndex()
{
    return m_takeUpIndex;
}
bool Gun::isDefaultGun()
{
    return m_isDefaultGun;
}
bool Gun::isCurrentGun()
{
    return m_isCurrentGun;
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
    if (m_isDefaultGun)
    {
        return m_bullets == m_magazieSize;
    }else
    {
        if (m_reloadType == 2)
        {
            return isHaveBullet();
        }
        if (m_totalBullets >= m_magazieSize)
        {
            return m_bullets == m_magazieSize;
        }else
        {
            return m_bullets == m_totalBullets;
        }
    }
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
    m_totalBullets += m_magazieSize;
    _G_U->setGunBulletNumber(m_id, m_totalBullets);
    int userGold = _G_U->getUserGold();
    userGold -= m_bulletPrice;
    _G_U->setUserGold(userGold);
}
int Gun::getBulletNum()
{
    return m_bullets;
}
int Gun::getTotalBulletNum()
{
    return m_totalBullets;
}
string Gun::getId()
{
    return m_id;
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

