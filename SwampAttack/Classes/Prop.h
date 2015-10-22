//
//  Prop.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/30.
//
//

#ifndef __SwampAttack__Prop__
#define __SwampAttack__Prop__


#include "json/json.h"
#include "BaseCode.h"
#include "GameSubject.h"
#include "GameObject.h"

using namespace std;

enum PropState
{
    p_normal,
    p_moveing,
    p_arrve,
    p_throw,
    p_readyToHurt,
    p_canToHurt,
    p_turning,
    p_dieing,
    p_die,
    p_canDelete,
};

class Prop : public GameSubject,public GameObject{
private:
    bool        m_isUnlock;
    int         m_num;
    bool        m_isTakeUp;
    int         m_takeUpIndex;
    
    PropState   m_state;
    Vec2        m_point;
    Vec2        m_viewPoint;
    
    float       m_timeDlay;
public:
    Prop(Json::Value value);
    ~Prop();
    void    setFightView();
    void    gameLoop(float data);
public:
    //---
    Rect    getPropRect();
    //---
    void    takeUp(int index);
    void    takeDown();
    void    setTakeUpIndex(int index);
    int     getTakeUpIndex();
    bool    isTakeUp();
    
    bool    isUnlock();
    bool    unlockProp();
    int     getNum();
    bool    buyProp();
    bool    useProp();
    void    addProp(int num);
    void    checkUnlock(Layer * layer);
    void    loadResource();
    //--- prop state ---
    void    setPropPoint(Vec2 point);
    Vec2    getPropPoint();
    Vec2    getPropViewPoint();
    bool    isCanArrve();
    
    void    arrveCall();
    void    throwCall();
    bool    checkCanToHurt();
    
    
    void    setStateMoveing();
    void    setStateArrve();
    void    setStateThrowing();
    void    setStateReadyToHurt();
    void    setStateCanToHurt();
    void    setStateDieing();
    void    setStateDie();
    void    setStateCanDelete();
    void    setStateNormal();
    void    setStateTurning();
    bool    isNormal();
    bool    isMoveing();
    bool    isArrve();
    bool    isThrowing();
    bool    isReadyToHurt();
    bool    isCanToHurt();
    bool    isDie();
    bool    isCanDelete();
    bool    isTurning();
    
private:
    int         m_index;
    string      m_id;           //
    string      m_itemName;         //
    string      m_modelId;      //
    float       m_effectArea;   //
    float       m_damage;       //
    float       m_vertigo;
    float       m_deceleration ;
    
    std::vector<string>  m_buffIds;
    float       m_time;
    int         m_itemPrice;
    string      m_unlockMission;
    int         m_unlockGold;
    string      m_itemDestription;
    int         m_limitLevel;
    
    int         m_strengthenGold;
    int         m_strengthenLevel;
    bool        m_isMaxLevel;
    string      m_unlockStr;
public:
    bool    isMaxLevel();
    bool    addStrengthenLevel();
    
    string      getId();
    string      getItemName();
    string      getModelId();
    float       getEffectArea();
    float       getDamage();
    float       getVertigo();
    float       getDeceleration();
    vector<string> getBuffId();
    string      getUnlockMisstion();
    int         getUnlockGold();
    string      getItemDestription();
    int         getPropPrice();
    int         getStrengthenGold();
    int         getStrengthenLevel();
    int         getLimitLevel();
    int         getIndex();
    string      getUnlockStr();
    
    //
    void        setIndex(int index);
};

#endif /* defined(__SwampAttack__Prop__) */
