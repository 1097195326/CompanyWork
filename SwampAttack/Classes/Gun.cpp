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


Gun::Gun(Json::Value data)
{
    
    m_id = data["Id"].asString() ;
    m_weaponName = data["WeaponName"].asString();
    m_modelId = data["ModelId"].asString();
    m_bulletModelId = data["BulletModelId"].asString();
    m_weaponType = data["WeaponType"].asString();
    m_strengthenLevel = atoi(data["StrengthenLevel"].asString().c_str());
    m_damage = atof(data["Damage"].asString().c_str());
    m_damageArea = atof(data["DamageArea"].asString().c_str());
    m_shrapnelNumber = atoi(data["ShrapnelNumber"].asString().c_str());
    m_critRate = atof(data["CritRate"].asString().c_str());
    m_critDamageRate = atof(data["CritDamageRate"].asString().c_str());
    m_accuracy = atof(data["Accuracy"].asString().c_str());
    m_fireRate = atof(data["FireRate"].asString().c_str());
    m_range = atof(data["Range"].asString().c_str());
    m_reloadSpeed = atof(data["ReloadSpeed"].asString().c_str());
    m_switchSpeed = atof(data["SwitchSpeed"].asString().c_str());
    m_ammunltionLimit = atoi(data["AmmunitionLimit"].asString().c_str());
    m_magazieSize = atoi(data["MagazineSize"].asString().c_str());
    m_bulletSpeed = atof(data["BulletSpeed"].asString().c_str());
    
    m_bullets = m_magazieSize;
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
void Gun::addBullet()
{
    ++m_bullets;
}
bool Gun::isFull()
{
    return m_bullets == m_magazieSize;
}
bool Gun::isHaveBullet()
{
    return m_bullets > 0;
}