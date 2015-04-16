//
//  GunManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/30.
//
//

#include "GunManager.h"
#include "ConfigManager.h"



GunManager::GunManager()
{
    addGun(defaultGunID);
    
    currentGun = m_gunData[defaultGunID];
}
GunManager::~GunManager()
{
    
}
GunManager * GunManager::getInstance()
{
    static GunManager gunManager;
    return &gunManager;
}

void GunManager::gameLoop(float data)
{
    
}
Gun * GunManager::getCurrentGun()
{
    return currentGun;
}
void GunManager::changeGun(string gunId)
{
    currentGun = m_gunData[gunId];
}
void GunManager::addGun(string gunId)
{
    Json::Value gunData = ConfigManager::getInstance()->getDataByTag("wuqi", gunId);
    m_gunData[gunId] = new Gun(gunData);
}