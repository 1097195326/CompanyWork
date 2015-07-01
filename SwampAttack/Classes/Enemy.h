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


using namespace std;

enum EnemyStatus
{
    e_clear   = 0b00000000000,
    e_waiting = 0b00000000001,
    e_dieing  = 0b00000000010,
    e_die     = 0b00000000100,
    e_walk    = 0b00000001000,
    e_wanderF = 0b00000010000,
    e_wanderB = 0b00000100000,
    e_hurt1   = 0b00001000000,
    e_hurt2   = 0b00010000000,
    e_hurt3   = 0b00100000000,
    e_attack  = 0b01000000000,
    e_canDel  = 0b10000000000,
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
    
    float   m_attackWaitTime;
    
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
    bool    isWeak();
    bool    isShowHurt();
    bool    isDieing();
    bool    isWalk();
    bool    isWanderF();
    bool    isWanderB();
    bool    isHurt();
    int     getHurtIndex();
    bool    isAttack();
    Vec2    getPosition();
    Vec2    getEnemyCenterPoint();
    Vec2    getTargetPosition();
    void    dieingCall();
    void    diedCall();
    void    attackCall();
    void    hurtCall();
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
    Vec2    getSpeedV();
    float   getSpeedF();
    float   getDamage();
    float   getAttackSpeed();
    int     getGoldForDied();
    string  getDrop();
};

#endif /* defined(__SwampAttack__Enemy__) */
