//
//  GameBuff.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/14.
//
//

#ifndef __SwampAttack__GameBuff__
#define __SwampAttack__GameBuff__

#include "json/json.h"
#include "BaseCode.h"
#include "GameObject.h"

class Enemy;

using namespace std;

enum GameBuffState
{
    g_b_normal,
    g_b_canHurt,
    g_b_waiting,
    g_b_die,
    g_b_canDelete,
};

class GameBuff : public GameObject{
private:
    GameBuffState m_state;
    float   m_delay;
    bool    m_isShow;
    int     m_frames;
    Enemy * m_enemy;
public:
    void    setEnemyModel(Enemy * enmey);
    void    removeFromModel();
    void    enemyDieCall();
    
    void    setDamage(float damage);
    void    setIsShow();
    void    setStateDie();
    void    setStateCanDelete();
    void    setStateWaiting();
    bool    isCanDelete();
    bool    isCanHurt();
    bool    isDie();
    bool    isShow();
public:
    GameBuff(Json::Value data);
    ~GameBuff();
    void    gameLoop(float data);
private:
    string      m_id;
    string      m_modelId;
    int         m_buffType;
    float       m_damage;
    float       m_percentageDamage;
    float       m_time;
public:
    string  getId();
    string  getModelId();
    int     getBuffType();
    float   getDamage();
    float   getPercentageDamage();
    float   getTime();
    int     getFrames();
    
};

#endif /* defined(__SwampAttack__GameBuff__) */
