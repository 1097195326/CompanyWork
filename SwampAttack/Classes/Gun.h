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

using namespace std;

class Gun {
private:
    string  m_id;
    string  m_weaponName;
    string  m_modelName;
    string  m_weaponType;
    int     m_strengthenLevel;
    float   m_damage;
    float   m_damageArea;
    int     m_shrapnelNumber;
    float   m_critRate;
    float   m_accuracy;
    float   m_fireRate;
    float   m_range;
    float   m_reloadSpeed;
    float   m_switchSpeed;
    int     m_ammunltionLimit;
    int     m_magazieSize;
    float   m_bulletSpeed;
public:
    Gun();
    ~Gun();
    
public:
    
};

#endif /* defined(__SwampAttack__Gun__) */
