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
    clear   = 0b00000000,
    waiting = 0b00000001,
    dieing  = 0b00000010,
    die     = 0b00000100,
    walk    = 0b00001000,
    hurt    = 0b00010000,
    attack  = 0b00100000,
    
};

class Enemy :public GameObject {
private:
    Json::Value m_data;
    int     m_status;
    
public:
    void    setView();
    
private:
    string  m_id;
    string  m_monsterName;
    string  m_modelId;
    string  m_actionType;
    int     m_level;
    float   m_health;
    Vec2    m_speed;
    float   m_damage;
    float   m_attackSpeed;
    int     m_gold;
    string  m_drop;

    Vec2    m_point;
    Vec2    m_targetPoint;
//    Vec2    m_maxSpeed;
//    Vec2    m_force;
//    float   m_mass;
    
public:
    Enemy(Json::Value data);
    ~Enemy();
    void    gameLoop(float data);
public:
    bool    isDieing();
    bool    isWalk();
    bool    isHurt();
    bool    isAttack();
    Vec2    getPosition();
    Vec2    getTargetPosition();
    //----
    string  getId();
    string  getMonsterName();
    string  getModelId();
    string  getActionType();
    int     getLevel();
    int     getHealthValue();
    Vec2    getSpeed();
    float   getDamage();
    float   getAttackSpeed();
    int     getGoldForDied();
    string  getDrop();
};

#endif /* defined(__SwampAttack__Enemy__) */
