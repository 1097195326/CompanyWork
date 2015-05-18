//
//  GuanQiaModels.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/8.
//
//

#include "GuanQiaModel.h"

GuanqiaModel::GuanqiaModel(Json::Value data):m_data(data)
{
    m_id = m_data["Id"].asString();
    m_instanceName = m_data["InstanceName"].asString();
    m_modelId = m_data["ModelId"].asString();
    m_instanceType = m_data["InstanceType"].asString();
    m_lastInstanceId = m_data["LastInstanceId"].asString();
    m_mapId = m_data["MapId"].asString();
    m_costPower = atoi(m_data["CostPower"].asString().c_str());
    m_throughGold =  atoi(m_data["ThroughGold"].asString().c_str());
    
}
GuanqiaModel::~GuanqiaModel()
{
    
}
#pragma get function
string GuanqiaModel::getId()
{
    return m_id;
}
string GuanqiaModel::getGuanqiaName()
{
    return m_instanceName;
}
string GuanqiaModel::getModelId()
{
    return m_modelId;
}
string GuanqiaModel::getInstanceType()
{
    return m_instanceType;
}
string GuanqiaModel::getLastInstanceId()
{
    return m_lastInstanceId;
}
string GuanqiaModel::getMapId()
{
    return m_mapId;
}
int GuanqiaModel::getCostPower()
{
    return m_costPower;
}
Json::Value GuanqiaModel::getMonsters()
{
    return m_data["MissionMonster"];
}
int  GuanqiaModel::getThroughGold()
{
    return m_throughGold;
}