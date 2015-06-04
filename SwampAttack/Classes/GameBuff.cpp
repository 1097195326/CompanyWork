//
//  GameBuff.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/14.
//
//

#include "GameBuff.h"

#include "Enemy.h"


class GameBuffInfo {
private:
    std::map<string,int> m_frames;
    GameBuffInfo()
    {
        m_frames["burn"] = 10;
        
    }
public:
    static GameBuffInfo * getInstance()
    {
        static GameBuffInfo buffInfo;
        return &buffInfo;
    }
    int getFrameByName(string name)
    {
        return m_frames[name];
    }
};

GameBuff::GameBuff(Json::Value data):
m_state(g_b_normal),
m_delay(0.0f),
m_isShow(false)
{
    m_enemy = NULL;
    
    m_id = data["BuffId"].asString() ;
    m_modelId= data["ModelId"].asString() ;
    m_buffType = atoi(data["BuffType"].asString().c_str());
    m_damage =
    data["Damage"].asString() == "" ?
    0 : atof(data["Damage"].asString().c_str());
    m_percentageDamage = atof(data["PercentageDamage"].asString().c_str());
    m_time = atof(data["Time"].asString().c_str());
    m_frames = GameBuffInfo::getInstance()->getFrameByName(m_modelId);
}
GameBuff::~GameBuff()
{
    
}
void GameBuff::gameLoop(float data)
{
    if (isCanDelete())
    {
        return;
    }
    m_delay += data;
    if (m_delay >=1)
    {
        m_state = g_b_canHurt;
        m_delay = 0.0f;
        m_time -= 1;
    }
    if (m_time <= 0)
    {
        m_state = g_b_die;
    }
}
void GameBuff::setEnemyModel(Enemy *enemy)
{
    m_enemy = enemy;
}
void GameBuff::removeFromModel()
{
    if (m_enemy)
    {
        m_enemy->moveBuff(this);
    }
}
void GameBuff::enemyDieCall()
{
    setStateDie();
    m_enemy = NULL;
}
void GameBuff::setIsShow()
{
    m_isShow = true;
}
void GameBuff::setStateDie()
{
    m_state = g_b_die;
}
void GameBuff::setStateCanDelete()
{
    m_state = g_b_canDelete;
}
void GameBuff::setStateWaiting()
{
    m_state = g_b_waiting;
}
bool GameBuff::isDie()
{
    return m_state == g_b_die;
}
bool GameBuff::isCanDelete()
{
    return m_state == g_b_canDelete;
}
bool GameBuff::isCanHurt()
{
    return m_state == g_b_canHurt;
}
bool GameBuff::isShow()
{
    return m_isShow;
}
//--- get
string GameBuff::getId()
{
    return m_id;
}
string GameBuff::getModelId()
{
    return m_modelId;
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
int GameBuff::getFrames()
{
    return m_frames;
}