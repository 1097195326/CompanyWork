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

DefenseBuildingManager::DefenseBuildingManager()
{
    GCCsvHelper * buildingHelper = _C_M->getCsvHelperByName("building");
    m_hashHead = buildingHelper->getHashHead();
    Json::Value data = buildingHelper->getJsonData();
    
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
            default:
                break;
        }
        
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