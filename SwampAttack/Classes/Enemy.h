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



using namespace std;

enum EnemyStatus
{
    e_clear   = 0b000000000,
    e_waiting = 0b000000001,
    e_dieing  = 0b000000010,
    e_die     = 0b000000100,
    e_walk    = 0b000001000,
    e_hurt1   = 0b000010000,
    e_hurt2   = 0b000100000,
    e_hurt3   = 0b001000000,
    e_attack  = 0b010000000,
    e_canDel  = 0b100000000,
};

class Enemy :public GameObject {
protected:
    Json::Value m_data;
    int     m_status;
    Rect    m_rect;
    bool    m_isShowHurt;
    bool    m_isWeak;
    
    float   dlay;
    float   tatolDlay;
    float   hurtDlay;       //受伤 记数
    
public:
    virtual void    setView();
    bool    isContainsPoint(Rect rect);
    void    hurt(int damage,int index);
    void    hurt(int damage);
protected:
    virtual void    move();
    
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
    bool    isHurt();
    int     getHurtIndex();
    bool    isAttack();
    Vec2    getPosition();
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
