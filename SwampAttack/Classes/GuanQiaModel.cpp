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
m_isUnlock(false),
m_isWin(false)
{
    m_id = m_data["MissionId"].asString();
    string missionName = m_data["MissionName"].asString();
    m_missionName = _C_M->getTranslateById(missionName);
    m_modelId = m_data["ModelId"].asString();
    m_missionType = m_data["MissionType"].asString();
    
    m_sceneIndex =  atoi(m_data["Scene"].asString().c_str());
    m_checkPoint =  atoi(m_data["Checkpoint"].asString().c_str());
    
//    log("m_sceneIndex:%d",m_sceneIndex);
//    log("m_checkPoint:%d",m_checkPoint);
//    m_lastInstanceId = m_data["LastInstanceId"].asString();
//    m_mapId = m_data["MapId"].asString();
//    m_costPower = atoi(m_data["CostPower"].asString().c_str());
    m_gold =  atoi(m_data["Gold"].asString().c_str());
    m_unlockMission = m_data["UnlockMission"].asString();
    m_dropId = m_data["Drop"].asString();
    m_shadeName = m_data["shade"].asString();
    
    
    m_isUnlock = _G_U->isUnlockGuanqia(m_id);
    m_isWin = _G_U->isWinGuanqia(m_id);
    
    Json::Value b_point = _C_M->getDataByName("guanqiaPoint", m_id, "iphone5s");
    Json::Value y_point = _C_M->getDataByName("guanqiaPoint", m_id, "iphone5s_yy");
//    log("point:%s",point.toStyledString().c_str());
    for (int i = 0; i < b_point.size(); ++i)
    {
        switch (i) {
            case 0:
                m_buttonPoint.x = atoi(b_point[i].asString().c_str());
                m_yinyingPoint.x = atoi(y_point[i].asString().c_str());
                break;
            case 1:
                m_buttonPoint.y = atoi(b_point[i].asString().c_str());
                m_yinyingPoint.y = atoi(y_point[i].asString().c_str());
                break;
            default:
                break;
        }
    }
}
GuanqiaModel::~GuanqiaModel()
{
    
}
bool GuanqiaModel::isWin()
{
    return m_isWin;
}
void GuanqiaModel::setGuanqiaWin()
{
    m_isWin = true;
    _G_U->setGuanqiaWin(m_id);
}
void GuanqiaModel::unlockGuanqia()
{
    m_isUnlock = true;
    _G_U->unlockGuanqia(m_id);
}
bool GuanqiaModel::isUnlock()
{
    return m_isUnlock;
}
Vec2 GuanqiaModel::getGuanqiaPoint()
{
    return m_buttonPoint;
}
Vec2 GuanqiaModel::getYinyingPoint()
{
    return m_yinyingPoint;
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
int GuanqiaModel::getSceneIndex()
{
    return m_sceneIndex;
}
int GuanqiaModel::getCheckPoint()
{
    return m_checkPoint;
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
string GuanqiaModel::getDropId()
{
    return m_dropId;
}
string GuanqiaModel::getShadeName()
{
    return m_shadeName;
}