//
//  GuanQiaModels.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/8.
//
//

#include "GuanQiaModel.h"
#include "GameUser.h"


GuanqiaModel::GuanqiaModel(Json::Value data):m_data(data),
m_isUnlock(false)
{
    m_id = m_data["MissionId"].asString();
    m_missionName = m_data["MissionName"].asString();
    m_modelId = m_data["ModelId"].asString();
    m_missionType = m_data["MissionType"].asString();
//    m_lastInstanceId = m_data["LastInstanceId"].asString();
//    m_mapId = m_data["MapId"].asString();
//    m_costPower = atoi(m_data["CostPower"].asString().c_str());
    m_gold =  atoi(m_data["Gold"].asString().c_str());
    m_unlockMission = m_data["UnlockMission"].asString();
    
    
    m_isUnlock = _G_U->isUnlockGuanqia(m_id);
    
    Json::Value point = _C_M->getDataByName("guanqiaPoint", m_id, "iphone5s");
//    log("point:%s",point.toStyledString().c_str());
    for (int i = 0; i < point.size(); ++i)
    {
        switch (i) {
            case 0:
                m_point.x = atoi(point[i].asString().c_str());
                break;
            case 1:
                m_point.y = atoi(point[i].asString().c_str());
                break;
            default:
                break;
        }
    }
}
GuanqiaModel::~GuanqiaModel()
{
    
}
void GuanqiaModel::unlockGuanqia()
{
    _G_U->unlockGuanqia(m_id);
}
bool GuanqiaModel::isUnlock()
{
    return m_isUnlock;
}
Vec2 GuanqiaModel::getGuanqiaPoint()
{
    return m_point;
}
#pragma get function
string GuanqiaModel::getId()
{
    return m_id;
}
string GuanqiaModel::getGuanqiaName()
{
    return m_missionName;
}
string GuanqiaModel::getModelId()
{
    return m_modelId;
}
string GuanqiaModel::getMissionType()
{
    return m_missionType;
}
//string GuanqiaModel::getLastInstanceId()
//{
//    return m_lastInstanceId;
//}
//string GuanqiaModel::getMapId()
//{
//    return m_mapId;
//}
//int GuanqiaModel::getCostPower()
//{
//    return m_costPower;
//}
string GuanqiaModel::getUnlockMission()
{
    return m_unlockMission;
}
Json::Value GuanqiaModel::getMonsters()
{
    return m_data["MissionMonster"];
}
int  GuanqiaModel::getThroughGold()
{
    return m_gold;
}