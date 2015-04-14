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
    lear    = 0b00000000,
    live    = 0b00000001,
    die     = 0b00000010,
    walk    = 0b00000100,
    hurt    = 0b00001000,
    attack  = 0b00010000,
    
};

class Enemy :public GameObject {
private:
    Json::Value m_data;
    EnemyStatus m_status;
    
public:
    
    
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
//    Vec2    m_maxSpeed;
//    Vec2    m_force;
//    float   m_mass;
    
public:
    Enemy(Json::Value data);
    ~Enemy();
    void    gameLoop(float data);
public:
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
