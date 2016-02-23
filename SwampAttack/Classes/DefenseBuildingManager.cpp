//
//  DefenseBuildingManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/14.
//
//

#include "DefenseBuildingManager.h"
#include "ConfigManager.h"
#include "DefenseBuilding1.h"
#include "DefenseBuilding2.h"
#include "DefenseBuilding3.h"
#include "DefenseBuilding4.h"

DefenseBuildingManager::DefenseBuildingManager()
{
    GCCsvHelper * buildingHelper = _C_M->getCsvHelperByName("building");
    m_hashHead = buildingHelper->getHashHead();
    Json::Value data = buildingHelper->getJsonData();
    
    int index = 0;
    std::map<int,std::string>::iterator iter;
    for (iter = m_hashHead.begin(); iter != m_hashHead.end(); ++iter) {
        string propId = iter->second;
        int type = atoi(data[propId]["DefenceType"].asString().c_str());
        switch (type) {
            case 1:
                m_buildingData[propId] = new DefenseBuilding1(data[propId]);
                break;
            case 2:
                m_buildingData[propId] = new DefenseBuilding2(data[propId]);
                break;
            case 3:
                m_buildingData[propId] = new DefenseBuilding3(data[propId]);
                break;
            case 4:
                m_buildingData[propId] = new DefenseBuilding4(data[propId]);
                break;
            default:
                m_buildingData[propId] = new DefenseBuilding(data[propId]);
                break;
        }
        if (m_buildingData[propId]->isUnlock() &&
            m_buildingData[propId]->isActivate())
        {
            m_buildingData[propId]->setShowIndex((int)m_showBuildingData.size());
            m_showBuildingData.push_back(m_buildingData[propId]);
        }
        m_buildingData[propId]->setIndex(index);
        ++index;
    }
}
DefenseBuildingManager::~DefenseBuildingManager()
{
    
}
DefenseBuildingManager * DefenseBuildingManager::getInstance()
{
    static DefenseBuildingManager manager;
    return &manager;
}
void DefenseBuildingManager::gameLoop(float data)
{
    std::map<string,DefenseBuilding *>::iterator iter;
    for (iter = m_buildingData.begin(); iter != m_buildingData.end(); ++iter) {
        DefenseBuilding * building = iter->second;
        building->gameLoop(data);
    }
}
void DefenseBuildingManager::setView()
{
    std::map<string,DefenseBuilding *>::iterator iter;
    for (iter = m_buildingData.begin(); iter != m_buildingData.end(); ++iter) {
        DefenseBuilding * building = iter->second;
        building->setView();
    }
}
void DefenseBuildingManager::checkUnlock(Layer * layer)
{
    std::map<string,DefenseBuilding *>::iterator iter;
    for (iter = m_buildingData.begin(); iter != m_buildingData.end(); ++iter) {
        DefenseBuilding * building = iter->second;
        building->checkUnlock(layer);
    }
}
std::map<string,DefenseBuilding *> DefenseBuildingManager::getBuildingData()
{
    return m_buildingData;
}
std::vector<DefenseBuilding *> DefenseBuildingManager::getShowBuildingData()
{
    return m_showBuildingData;
}
DefenseBuilding * DefenseBuildingManager::getShowBuildingByIndex(int index)
{
    return m_showBuildingData[index];
}
int DefenseBuildingManager::getShowBuildingNum()
{
    return (int)m_showBuildingData.size();
}
void DefenseBuildingManager::addShowBuilding(DefenseBuilding * building)
{
    building->setShowIndex((int)m_showBuildingData.size());
    m_showBuildingData.push_back(building);
}
void DefenseBuildingManager::addBuildingJishudian()
{
    auto iter = m_showBuildingData.begin();
    for (; iter != m_showBuildingData.end(); ++iter)
    {
        (*iter)->addBuildingJishudian();
    }
}
DefenseBuilding * DefenseBuildingManager::getBuildingByIndex(int index)
{
    string propId = m_hashHead[index];
    return m_buildingData[propId];
}
int DefenseBuildingManager::getBuildingNum()
{
    return (int)m_buildingData.size();
}