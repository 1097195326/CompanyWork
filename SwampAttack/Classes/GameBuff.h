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

using namespace std;

class GameBuff {
private:
    
public:
    GameBuff(Json::Value data);
    ~GameBuff();
    
private:
    string      m_id;
    int         m_buffType;
    float       m_damage;
    float       m_percentageDamage;
    float       m_time;
public:
    string  getId();
    int     getBuffType();
    float   getDamage();
    float   getPercentageDamage();
    float   getTime();
    
};

#endif /* defined(__SwampAttack__GameBuff__) */
