//
//  GunManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/30.
//
//

#include "GunManager.h"
#include "ConfigManager.h"
#include "Human.h"


GunManager::GunManager()
{
    GCCsvHelper * gunHelper = _C_M->getCsvHelperByName("wuqi");
    m_hashHead = gunHelper->getHashHead();
    Json::Value data = gunHelper->getJsonData();
    std::map<int,std::string>::iterator iter;
    for (iter = m_hashHead.begin(); iter != m_hashHead.end(); ++iter) {
        string gunId = iter->second;
        Gun * gun = new Gun(data[gunId]);
        m_gunData[gunId] = gun;
        if (gun->isTakeUp())
        {
            m_takeUpGunData[gunId] = gun;
        }
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
int GunManager::getTakeUpGunNum()
{
    return (int)m_takeUpGunData.size();
}
int GunManager::getTakeUpGunIndex(string gunId)
{
    int index = 0;
    std::map<string,Gun *>::iterator iter;
    for (iter = m_takeUpGunData.begin(); iter != m_takeUpGunData.end(); ++iter)
    {
        ++index;
        if (iter->first == gunId)
        {
            break;
        }
    }
    return index;
}
void GunManager::takeUpGun(string gunId)
{
    int index = (int)m_takeUpGunData.size() + 1;
    m_gunData[gunId]->takeUp(index);
    m_takeUpGunData[gunId] = m_gunData[gunId];
}
void GunManager::takeDownGun(string gunId)
{
    m_gunData[gunId]->takeDown();
    m_takeUpGunData.erase(gunId);
}
Gun * GunManager::getCurrentGun()
{
    return currentGun;
}
void GunManager::changeGun(string gunId)
{
    if(m_takeUpGunData[gunId]->getTotalBulletNum() < 1)
    {
        return;
    }
    std::map<string,Gun *>::iterator iter;
    for (iter = m_takeUpGunData.begin(); iter != m_takeUpGunData.end(); ++iter)
    {
        Gun * gun = iter->second;
        if (iter->first == gunId)
        {
            gun->setIsCurrentGun(true);
            currentGun = m_takeUpGunData[gunId];
        }else
        {
            gun->setIsCurrentGun(false);
        }
        gun->notify();
    }
    
    Human::getInstance()->changeGun(currentGun);
    
}
void GunManager::setFightView()
{
    std::map<string,Gun *>::iterator iter;
    for (iter = m_takeUpGunData.begin(); iter != m_takeUpGunData.end(); ++iter)
    {
        Gun * _gun = iter->second;
        _gun->setFightView();
    }
}
void GunManager::setShopView()
{
    std::map<string,Gun *>::iterator iter;
    for (iter = m_takeUpGunData.begin(); iter != m_takeUpGunData.end(); ++iter)
    {
        Gun * _gun = iter->second;
//        _gun->setView();
    }
}