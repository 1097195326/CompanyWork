//
//  GameBuff.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/14.
//
//

#include "GameBuff.h"


GameBuff::GameBuff(Json::Value data)
{
    m_id = data["BuffId"].asString() ;
    m_buffType = atoi(data["BuffType"].asString().c_str());
    m_damage =
    data["Damage"].asString() == "" ?
    0 : atof(data["Damage"].asString().c_str());
    m_percentageDamage = atof(data["PercentageDamage"].asString().c_str());
    m_time = atof(data["Time"].asString().c_str());
    
}
GameBuff::~GameBuff()
{
    
}
string GameBuff::getId()
{
    return m_id;
}
int GameBuff::getBuffType()
{
    return m_buffType;
}
float GameBuff::getDamage()
{
    return m_damage;
}
float GameBuff::getPercentageDamage()
{
    return m_percentageDamage;
}
float GameBuff::getTime()
{
    return m_time;
}