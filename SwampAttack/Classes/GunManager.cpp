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
#include "ShopGunIcon.h"


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
//            log("gun take up index :%d",gun->getTakeUpIndex());
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
Gun * GunManager::getTakeUpGunByIndex(int index)
{
    Gun * gun = NULL;
//    int i = 0;
    std::map<string,Gun *>::iterator iter;
    for (iter = m_takeUpGunData.begin(); iter != m_takeUpGunData.end(); ++iter)
    {
        if (index == iter->second->getTakeUpIndex()) {
            gun = iter->second;
            break;
        }
//        ++i;
    }
    return gun;
}
int GunManager::getTakeUpGunIndexByName(string name)
{
    int index = 0;
    std::map<string,Gun *>::iterator iter;
    for (iter = m_takeUpGunData.begin(); iter != m_takeUpGunData.end(); ++iter)
    {
        ++index;
        if (iter->first == name) {
            break;
        }
    }
    return index;
}
std::map<string,Gun *> GunManager::getTakeUpGunData()
{
    return m_takeUpGunData;
}
void GunManager::takeUpGun(string gunId)
{
    int index = (int)m_takeUpGunData.size();
    Gun * gun = m_gunData[gunId];
    if (index >= 3)
    {
        Gun * lastGun = getTakeUpGunByIndex(3);
        takeDownGun(lastGun->getId());
        
        gun->takeUp(index);
        m_takeUpGunData[gunId] = gun;
        m_GunIcons[index -1]->reSetIcon(gun);
    }else
    {
        for (int i = 0; i < 3; ++i)
        {
            if (!m_GunIcons[i]->isHaveGun())
            {
                gun->takeUp(i + 1);
                m_takeUpGunData[gunId] = gun;
                m_GunIcons[i]->reSetIcon(gun);
                break;
            }
        }
    }
    
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
    if (Human::getInstance()->isChange())
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
void GunManager::setShopView(Sprite * gunItemSprite)
{
    m_GunIcons.reserve(3);
    for (int i = 0; i < 3; i++)
    {
        Gun * gun = getTakeUpGunByIndex(i+1);
        ShopGunIcon * icon = new ShopGunIcon(i);
        icon->reSetIcon(gun);
        gunItemSprite->addChild(icon);
        m_GunIcons[i] = icon;
    }
}
void GunManager::checkUnlock()
{
    std::map<string,Gun *>::iterator iter;
    for (iter = m_gunData.begin(); iter != m_gunData.end(); ++iter)
    {
        Gun * _gun = iter->second;
        _gun->checkUnlock();
    }
}