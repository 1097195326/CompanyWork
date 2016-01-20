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
    
    int     m_sceneIndex;
    int     m_checkPoint;
//    string  m_lastInstanceId;
//    string  m_mapId;
//    int     m_costPower;
    
    string  m_unlockMission;
    int     m_gold;
    string  m_shadeName;
    string  m_dropId;
    
    bool    m_isUnlock;
    bool    m_isWin;
    Vec2    m_buttonPoint;
    Vec2    m_yinyingPoint;
public:
    bool    isWin();
    void    setGuanqiaWin();
    bool    isUnlock();
    void    unlockGuanqia();
    Vec2    getGuanqiaPoint();
    Vec2    getYinyingPoint();
public:
    
    GuanqiaModel(Json::Value data);
    ~GuanqiaModel();
    
public:
    string  getId();
    string  getGuanqiaName();
    string  getModelId();
    string  getMissionType();
    int     getSceneIndex();
    int     getCheckPoint();
//    string  getLastInstanceId();
//    string  getMapId();
//    int     getCostPower();
    int     getThroughGold();
    string  getUnlockMission();
    string  getDropId();
    string  getShadeName();
    Json::Value    getMonsters();
    
};

#endif /* defined(__SwampAttack__GuanQiaModels__) */
