//
//  Gun.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/30.
//
//

#ifndef __SwampAttack__Gun__
#define __SwampAttack__Gun__

#include "json/json.h"
#include "BaseCode.h"
#include "GameObject.h"


using namespace std;

enum GunStatus
{
    g_normal,
    g_fire,
    g_stop,
    g_reload,
    g_have,
    g_empty,
    
};

class Gun : public GameObject{
private:
    
public:
    void    fire(Touch * touch, Event * event);
    void    stop();
    
    bool    isFire();
    bool    isReload();
    bool    isStop();
    bool    isHave();
    bool    isEmpty();
private:
    string  m_id;
    string  m_weaponName;
    string  m_modelId;
    string  m_bulletModelId;
    string  m_weaponType;
    int     m_strengthenLevel;
    float   m_damage;
    float   m_damageArea;
    int     m_shrapnelNumber;
    float   m_critRate;
    float   m_critDamageRate;
    float   m_accuracy;
    float   m_fireRate;
    float   m_range;
    float   m_reloadSpeed;
    float   m_switchSpeed;
    int     m_ammunltionLimit;
    int     m_magazieSize;
    float   m_bulletSpeed;
public:
    Gun(Json::Value data);
    ~Gun();
    void    gameLoop(float data);
public:
    
};

#endif /* defined(__SwampAttack__Gun__) */
