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
#include "GameSubject.h"

using namespace std;

class GuanqiaModel : public GameSubject {
private:
    Json::Value m_data;
    
    string  m_id;
    string  m_missionName;
    string  m_modelId;
    string  m_missionType;
//    string  m_lastInstanceId;
//    string  m_mapId;
//    int     m_costPower;
    string  m_unlockMission;
    int     m_gold;
    
    bool    m_isUnlock;
    Vec2    m_point;
public:
    
    bool    isUnlock();
    void    unlockGuanqia();
    Vec2    getGuanqiaPoint();
public:
    
    GuanqiaModel(Json::Value data);
    ~GuanqiaModel();
    
public:
    string  getId();
    string  getGuanqiaName();
    string  getModelId();
    string  getMissionType();
//    string  getLastInstanceId();
//    string  getMapId();
//    int     getCostPower();
    int     getThroughGold();
    string  getUnlockMission();
    Json::Value    getMonsters();
    
};

#endif /* defined(__SwampAttack__GuanQiaModels__) */
