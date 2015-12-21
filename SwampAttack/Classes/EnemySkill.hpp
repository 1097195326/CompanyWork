//
//  EnemySkill.hpp
//  SwampAttack
//
//  Created by oceantech02 on 15/12/21.
//
//

#ifndef EnemySkill_hpp
#define EnemySkill_hpp

//#include "Enemy.h"
#include "ConfigManager.h"

using std::string;

class Enemy;


class EnemySkill {
private:
    Enemy * m_enmey;
    
    string  m_id;
    string  m_idName;           //
    int     m_type;             //
    float   m_hp;               //血量 百分比
    float   m_time;             //时间 间隔
    float   m_probablillity;    //出现 概率
    float   m_accelerate;       //加速 比例
    float   m_defense;          //防御时间
    float   m_long;             //远程 伤害
    float   m_dodge;            //闪避 时间
    
    Json::Value m_splitting;    //分裂 怪物
    Json::Value m_call;         //召唤 怪物
    
public:
    EnemySkill(string id);
    void    setEnemy(Enemy * enemy);
    virtual void run(float timeStep);
};

#endif /* EnemySkill_hpp */
