//
//  DefenseBuildingManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/14.
//
//

#include "DefenseBuildingManager.h"
#include "ConfigManager.h"


DefenseBuildingManager::DefenseBuildingManager()
{
    GCCsvHelper * buildingHelper = _C_M->getCsvHelperByName("building");
    m_hashHead = buildingHelper->getHashHead();
    Json::Value data = buildingHelper->getJsonData();
    
    std::map<int,std::string>::iterator iter;
    for (iter = m_hashHead.begin(); iter != m_hashHead.end(); ++iter) {
        string propId = iter->second;
        m_buildingData[propId] = new DefenseBuilding(data[propId]);
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
std::map<string,DefenseBuilding *> DefenseBuildingManager::getBuildingData()
{
    return m_buildingData;
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