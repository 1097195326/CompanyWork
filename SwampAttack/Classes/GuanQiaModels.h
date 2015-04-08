//
//  GuanQiaModels.h
//  SwampAttack
//
//  Created by oceantech02 on 15/4/8.
//
//

#ifndef __SwampAttack__GuanQiaModels__
#define __SwampAttack__GuanQiaModels__

#include "ConfigManager.h"

using namespace std;

class GuanqiaModel {
private:
    Json::Value m_data;
    
    string  m_id;
    string  m_instanceName;
    string  m_modelId;
    string  m_instanceType;
    string  m_lastInstanceId;
    string  m_mapId;
    int     m_costPower;
    int     m_throughGold;
private:
    
public:
    GuanqiaModel(Json::Value data);
    ~GuanqiaModel();
    
public:
    string  getId();
    string  getGuanqiaName();
    string  getModelId();
    string  getInstanceType();
    string  getLastInstanceId();
    string  getMapId();
    int     getCostPower();
    int     getThroughGold();
    Json::Value    getMonsters();
    
};

#endif /* defined(__SwampAttack__GuanQiaModels__) */
