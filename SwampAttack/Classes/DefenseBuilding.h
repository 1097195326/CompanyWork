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
#include "GameSubject.h"

class Enemy;

enum DefenseState
{
    d_normal,
    d_wait,
    d_canHurt,
    d_hurting,
};
using namespace std;

class DefenseBuilding : public GameObject, public GameSubject{
public:
    DefenseBuilding(Json::Value data);
    ~DefenseBuilding();
    void    gameLoop(float data);
public:
    virtual void    setView();
    virtual void    hurtEnemy(Enemy * enemy);
    virtual void    hurtCall();
    
    bool    isCanHurt();
    bool    isStateHurting();
    bool    isStateWait();
    
    virtual void    setStateWait();
    virtual void    setStateCanhurt();
    virtual void    setStateHurting();
    
    void    checkUnlock(Layer * layer);
    
    bool    isInRange(Vec2 point);
    
    void    addBuildingJishudian();
    int     getBuildingJishu();
protected:
    DefenseState m_state;
    int         m_index;
    int         m_showIndex;
    Vec2        m_point;
    float       m_waitDelay;
    int         m_jishu;
    //--- ---
    string      m_id;
    string      m_defenceName;
    string      m_modelId;
    string      m_bulletModelId;
    int         m_defenceType;
    float       m_damageArea;
    string      m_unlockMission;
    int         m_unlockGold;
    string      m_defenceDescription;
    string      m_unlockStr;
    int         m_limitLevel;
    int         m_activate;
    //
    int         m_strengthenLevel;
    int         m_hp;
    int         m_damage;
    int         m_number;
    int         m_beatback;
    int         m_deadnumber;
    float       m_deceleration;
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
    string  getUnlockStr();
    int     getLimitLevel();
    bool    isActivate();
    //
    int     getStrengthLevel();
    int     getHp();
    int     getDamage();
    int     getNumber();
    int     getBeatBack();
    int     getDeadNumber();
    int     getStrengthGold();
    int     getIndex();
    int     getShowIndex();
    //---
    
    void    setIndex(int index);
    void    setShowIndex(int index);
    
    
};

#endif /* defined(__SwampAttack__DefenseBuilding__) */
