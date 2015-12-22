//
//  Enemy.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#ifndef __SwampAttack__Enemy__
#define __SwampAttack__Enemy__

#include "BaseCode.h"
#include "GameObject.h"
#include "json/json.h"

#include "GameBuff.h"
//#include "EnemySkill.hpp"


using namespace std;

enum EnemyStatus
{
    e_clear   = 0 << 0,
    e_waiting = 1 << 0,
    e_dieing  = 1 << 1,
    e_die     = 1 << 2,
    e_walk    = 1 << 3,
    e_wanderF = 1 << 4,
    e_wanderB = 1 << 5,
    e_hurt1   = 1 << 6,
    e_hurt2   = 1 << 7,
    e_hurt3   = 1 << 8,
    e_attack  = 1 << 9,
    e_canDel  = 1 << 10,
    e_dianji  = 1 << 11,
    e_tanfei  = 1 << 12,
    e_kuangbao= 1 << 13,
    e_zhaohuan= 1 << 14,
    e_fenlie  = 1 << 15,
    e_farattack=1 << 16,
    e_fangyu  = 1 << 17,
    e_shanbi  = 1 << 18,
    
};

class Enemy :public GameObject {
protected:
    Json::Value m_data;
    int     m_status;
    Rect    m_rect;
    bool    m_isShowHurt;
    bool    m_isWeak;
    bool    m_isStop;
    
    float   dlay;
    float   tatolDlay;
    float   hurtDlay;       //受伤 记数
    
    float   m_dianjiDlay;      // 震荡弹 记数
    float   m_dianjiCount;
    Vec2    m_effectSpeedV;  //
    
    float   m_attackWaitTime;
    
//    EnemySkill * m_skill;
    
    std::list<GameBuff *>   m_buffData;
    
public:
    void    stopGame();
    void    continueGame();
    bool    isStopGame();
    virtual void    setView();
    bool    isContainsPoint(Rect rect);
    void    hurt(int damage,int index);
    virtual void    hurt(int damage);
    virtual void    effectAction(Vec2 point);
    void    hurtYun(float dlay);
    void    hurtJiansu(float su);
    void    effectSpeedByPer(float percent);
    void    hurtTanfei();
    void    addBuff(GameBuff * buff);
    void    moveBuff(GameBuff * buff);
    bool    isHaveBuff();
    std::list<GameBuff *>  getBuffData();
    void    removeAllBuffS();
    float   getAttackWaitTime();
protected:
    virtual void    move();
    virtual bool    computeIfWander();
    virtual void    wander();
protected:
    string  m_id;
    string  m_monsterName;
    string  m_modelId;
    string  m_capId;
    int     m_width;
    int     m_height;
    int     m_actionType;
    string  m_bulletModelId;
    int     m_attackType;
    float   m_bulletSpeed;
    int     m_level;
    float   m_health;
    float   m_totalHealth;
    Vec2    m_speedV;
    float   m_speedF;
    float   m_damage;
    float   m_attackSpeed;
    float   m_range;
    int     m_gold;
    string  m_drop;

    Vec2    m_point;
    Vec2    m_targetPoint;
//    Vec2    m_maxSpeed;
//    Vec2    m_force;
//    float   m_mass;
    
public:
    Enemy(Json::Value data);
    virtual ~Enemy();
    void    gameLoop(float data);
public:
    //--- view 接口
    // -- skill
    bool    isKuangbao();
    bool    isZhaohuan();
    bool    isFenlie();
    bool    isFarAttack();
    bool    isFangyu();
    bool    isShanbi();
    void    setStateKuangbao();
    void    setStateZhaohuan();
    void    setStateFenlie();
    void    setStateFarattack();
    void    setStateFangyu();
    void    setStateShanbi();
    
    void    setStateClear();
    
    bool    isTanfei();
    bool    isDianji();
    bool    isWeak();
    bool    isShowHurt();
    bool    isDieing();
    bool    isWalk();
    bool    isWanderF();
    bool    isWanderB();
    bool    isHurt();
    int     getHurtIndex();
    bool    isAttack();
    bool    isBoss();
    Vec2    getPosition();
    Vec2    getEnemyCenterPoint();
    Vec2    getTargetPosition();
    void    dieingCall();
    void    diedCall();
    void    attackCall();
    void    hurtCall();
    void    dianjiCall();
//    void    hurtTanfeiCall();
    bool    isCanDelete();
    //--- interface for
    bool    isDied();
    //--- 获得 基本 属性
    string  getId();
    string  getMonsterName();
    string  getModelId();
    string  getCapId();
    int     getAttackFrame();
    int     getWidth();
    int     getHeight();
    int     getActionType();
    string  getBulletModelId();
    int     getAttackType();
    float   getBulletSpeed();
    int     getLevel();
    int     getHealthValue();
    float   getHealthPercent();
    int     getTotalHealth();
    Vec2    getSpeedV();
    float   getSpeedF();
    float   getDamage();
    float   getAttackSpeed();
    int     getGoldForDied();
    string  getDrop();
    
    Rect    getRect();
};

#endif /* defined(__SwampAttack__Enemy__) */
