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
    m_hashHead = gunHelper->getHashHead();
    Json::Value data = gunHelper->getJsonData();
    std::map<int,std::string>::iterator iter;
    for (iter = m_hashHead.begin(); iter != m_hashHead.end(); ++iter) {
        string gunId = iter->second;
        m_gunData[gunId] = new Gun(data[gunId]);
    }
    
    currentGun = m_gunData[defaultGunID];
    m_canUseGunData[0] = currentGun;
    
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
Gun * GunManager::getGunByIndex(int index)
{
    string gunId = m_hashHead[index];
    return m_gunData[gunId];
}
int GunManager::getGunNum()
{
//    std::map<string,Gun *>::iterator iter;
//    for (iter = m_gunData.begin(); iter != m_gunData.end(); iter++) {
//        log("-s:%s",iter->first.c_str());
//    }
    return (int)m_gunData.size();
}
Gun * GunManager::getCurrentGun()
{
    return currentGun;
}
void GunManager::changeGun(string gunId)
{
    currentGun = m_gunData[gunId];
}