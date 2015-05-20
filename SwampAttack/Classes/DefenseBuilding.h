//
//  DefenseBuilding.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/14.
//
//

#ifndef __SwampAttack__DefenseBuilding__
#define __SwampAttack__DefenseBuilding__

#include "json/json.h"
#include "GameObject.h"
#include "BaseCode.h"


enum DefenseState
{
    d_normal,
    d_wait,
    d_hurt,
};
using namespace std;

class DefenseBuilding : public GameObject{
public:
    DefenseBuilding(Json::Value data);
    ~DefenseBuilding();
    void    gameLoop(float data);
public:
    void    setView();
    
    bool    isCanHurt();
    bool    isInRange(Vec2 point);
    void    fire(Vec2 position);
private:
    DefenseState m_state;
    float       m_index;
    Vec2        m_point;
    //--- ---
    string      m_id;
    string      m_defenceName;
    string      m_modelId;
    int         m_defenceType;
    float       m_damageArea;
    string      m_unlockMission;
    int         m_unlockGold;
    string      m_defenceDescription;
    int         m_limitLevel;
    //
    int         m_strengthenLevel;
    int         m_hp;
    int         m_damage;
    int         m_strengthenGold;
    
    bool        m_isUnlock;
    bool        m_isMaxLevel;
    
public:
    bool    isUnlock();
    void    unlockBuilding();
    bool    isMaxLevel();
    void    addStrengthenLevel();
    
    string  getId();
    string  getDefenceName();
    string  getModelId();
    int     getDefenceType();
    float   getDamageArea();
    string  getUnlockMission();
    int     getUnlockGold();
    string  getDefenceDescription();
    int     getLimitLevel();
    //
    int     getStrengthLevel();
    int     getHp();
    int     getDamage();
    int     getStrengthGold();
    
};

#endif /* defined(__SwampAttack__DefenseBuilding__) */
