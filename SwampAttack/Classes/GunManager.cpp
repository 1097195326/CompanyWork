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
    GCCsvHelper * gunHelper = _C_M->getCsvHelperByName("wuqi");
    std::map<int,std::string> hashHead = gunHelper->getHashHead();
    Json::Value data = gunHelper->getJsonData();
    std::map<int,std::string>::iterator iter;
    for (iter = hashHead.begin(); iter != hashHead.end(); ++iter) {
        string gunId = iter->second;
        m_gunData[gunId] = new Gun(data[gunId]);
    }
    
    
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