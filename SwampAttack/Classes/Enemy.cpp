//
//  Enemy.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "Enemy.h"
#include "GameMapManager.h"
#include "EnemyInfo.h"
#include "House.h"
#include "BulletManager.h"
#include "DropManager.h"
#include "GameDirector.h"


Enemy::Enemy(Json::Value data):
m_data(data),
m_isShowHurt(false),
m_isWeak(false),
m_isStop(false),
m_attackWaitTime(0.0f),
m_dianjiDlay(0.0f)
{
    m_actionType = atoi(m_data["ActionType"].asString().c_str());
    
    GameMap * gameMap = GameMapManager::getInstance()->getGameMap();
    switch (m_actionType) {
        case 1:
        {
            m_point = gameMap->enemy_start_buttomPoint + Vec2(0, random(0, gameMap->enemy_start_upline));
            if (m_point.y > gameMap->enemy_target_buttomPoint.y + gameMap->enemy_target_upline)
            {
                m_targetPoint.y = gameMap->enemy_target_buttomPoint.y + gameMap->enemy_target_upline;
            }else if (m_point.y < gameMap->enemy_target_buttomPoint.y)
            {
                m_targetPoint.y = gameMap->enemy_target_buttomPoint.y;
            }else
            {
                m_targetPoint.y = m_point.y;
            }
            m_targetPoint.x = gameMap->enemy_target_buttomPoint.x;
        }
            break;
        case 2:
        {
            m_point = gameMap->flyEnemy_start_buttomPoint + Vec2(0, random(0, gameMap->flyEnemy_start_upline));
            m_targetPoint = gameMap->flyEnemy_target_buttomPoint;
        }
            break;
        default:
            break;
    }
    
    ///--- set status ---
    m_status = e_clear;
    ///------set data-------
    m_id = m_data["Id"].asString();
    m_monsterName = m_data["MonsterName"].asString();
    m_modelId = m_data["ModelId"].asString();
    m_capId = m_data["CapId"].asString();
    m_width = EnemyInfo::getInstance()->getInfoByName(m_modelId).width;
    m_height = EnemyInfo::getInstance()->getInfoByName(m_modelId).height;
    
    m_bulletModelId = m_data["BulletModelId"].asString();
    m_attackType = atoi(m_data["AttackType"].asString().c_str());
    m_bulletSpeed = atof(m_data["BulletSpeed"].asString().c_str());
    m_level = atoi(m_data["Level"].asString().c_str());
    m_totalHealth = m_health = atoi(m_data["Hp"].asString().c_str());
    m_speedF = atof(m_data["Speed"].asString().c_str());
    m_damage = atof(m_data["Damage"].asString().c_str());
    
    m_speedV = m_targetPoint - m_point;
    m_speedV.normalize();
    m_speedV = m_speedV * m_speedF;
    
    float as = atof(m_data["AttackSpeed"].asString().c_str()) ;
    float af = EnemyInfo::getInstance()->getInfoByName(m_modelId).attackFrames;
    m_attackSpeed = 1.0f / as / af ;
    
    if(m_attackSpeed > 0.08f)
    {
        float   cha = m_attackSpeed - 0.08f;
        m_attackWaitTime = cha * af;
        m_attackSpeed = 0.08f;
    }
    
    m_range = atof(m_data["Range"].asString().c_str());
    m_gold = atoi(m_data["Gold"].asString().c_str());
    m_drop = m_data["Drop"].asString();
    
    dlay = 0;
    tatolDlay = random(0, 130) / 100.0f;
    hurtDlay = 0;
//    log("enemy model :%s",m_modelId.c_str());
}
Enemy::~Enemy()
{
//    log("enemy delete");
}
void Enemy::gameLoop(float data){}
void Enemy::move(){}
bool Enemy::computeIfWander(){return false;}
void Enemy::wander(){}
void Enemy::setView(){}
void Enemy::effectAction(cocos2d::Vec2 point){}
void Enemy::stopGame()
{
    m_isStop = true;
}
void Enemy::continueGame()
{
    m_isStop = false;
}
bool Enemy::isStopGame()
{
    return m_isStop;
}
void Enemy::addBuff(GameBuff *buff)
{
    m_buffData.push_back(buff);
}
void Enemy::moveBuff(GameBuff *buff)
{
    m_buffData.remove(buff);
}
bool Enemy::isHaveBuff()
{
    return m_buffData.size() > 0;
}
std::list<GameBuff *>  Enemy::getBuffData()
{
    return m_buffData;
}
void Enemy::removeAllBuffS()
{
    std::list<GameBuff *>::iterator iter;
    for (iter = m_buffData.begin(); iter != m_buffData.end();)
    {
        GameBuff * buff = *iter;
        buff->enemyDieCall();
        m_buffData.erase(iter++);
        
    }
}
float Enemy::getAttackWaitTime()
{
    return m_attackWaitTime;
}
bool Enemy::isContainsPoint(cocos2d::Rect rect)
{
    m_rect = Rect(m_point.x, m_point.y, m_width, m_height);
    return m_rect.intersectsRect(rect);
}
void Enemy::hurt(int damage,int index)
{
    if (isDieing() || isCanDelete())
    {
        return;
    }
    if (m_point.x > m_visibleOrigin.x + m_visibleSize.width + 30)
    {
        return;
    }
    m_health = m_health - damage;
    
    if (!m_isWeak && m_health < m_totalHealth * 0.5) {
        m_isWeak =true;
    }
    
    if (m_health <= 0)
    {
        removeAllBuffS();
        m_status &= e_clear;
        m_status |= e_dieing;
        m_isShowHurt = false;
        DropManager::getInstance()->dropObject(m_drop, m_point);
        _G_D->addGold(m_gold);
    }else if (m_status & e_dianji)
    {
        hurtDlay = 0;
        m_isShowHurt = true;
    }else
    {
        hurtDlay = 0;
        m_isShowHurt = true;
        m_status &= e_clear;
        switch (index) {
            case 1:
                m_status |= e_hurt1;
                break;
            case 2:
                m_status |= e_hurt2;
                break;
            case 3:
                m_status |= e_hurt3;
                break;
        }
    }
//    log("enemy health :%f",m_health);
}
void Enemy::hurt(int damage)
{
    if (isDieing() || isCanDelete())
    {
        return;
    }
    if (m_point.x > m_visibleOrigin.x + m_visibleSize.width+ 30)
    {
        return;
    }
    m_health = m_health - damage;
    if (m_health <= 0)
    {
        removeAllBuffS();
        m_status &= e_clear;
        m_status |= e_dieing;
        m_isShowHurt = false;
        DropManager::getInstance()->dropObject(m_drop, m_point);
        _G_D->addGold(m_gold);
    }else
    {
        hurtDlay = 0;
        m_isShowHurt = true;
    }
//    log("enemy health2 :%f",m_health);
}
void Enemy::hurtYun(float dlay)
{
    if (!(m_status & e_die || m_status & e_dieing))
    {
        m_status &= e_clear;
        m_status |= e_dianji;
        m_dianjiCount = dlay;
    }
}
void Enemy::hurtJiansu(float su)
{
    Vec2 effectSpeedV = m_speedV;
    effectSpeedV.normalize();
    effectSpeedV *= -su;
    
    m_effectSpeedV += effectSpeedV;
}
void Enemy::hurtTanfei()
{
    m_status &= e_clear;
    m_status |= e_tanfei;
}
//--- view 接口
bool Enemy::isTanfei()
{
    return m_status & e_tanfei;
}
bool Enemy::isDianji()
{
    return m_status & e_dianji;
}
bool Enemy::isWeak()
{
    return m_isWeak;
}
bool Enemy::isShowHurt()
{
    return m_isShowHurt;
}
bool Enemy::isDieing()
{
    return m_status & e_dieing;
}
bool Enemy::isWalk()
{
    return m_status & e_walk;
}
bool Enemy::isWanderF()
{
    return m_status & e_wanderF;
}
bool Enemy::isWanderB()
{
    return m_status & e_wanderB;
}
bool Enemy::isHurt()
{
    return m_status & e_hurt1 || m_status & e_hurt2 || m_status & e_hurt3;
}
int Enemy::getHurtIndex()
{
    switch (m_status) {
        case e_hurt1:
            return 1;
            break;
        case e_hurt2:
            return 2;
            break;
        case e_hurt3:
            return 3;
            break;
        default:
            return 0;
            break;
    }
}
bool Enemy::isBoss()
{
    bool isB = false;
    
    if (m_id == "200001") {
        isB = true;
    }else if (m_id == "200002")
    {
        isB = true;
    }else if (m_id == "200003")
    {
        isB = true;
    }else if (m_id == "200004")
    {
        isB = true;
    }
    
    return isB;
}
bool Enemy::isAttack()
{
    return m_status & e_attack;
}
bool Enemy::isDied()
{
    return m_status & e_die;
}
bool Enemy::isCanDelete()
{
    return m_status & e_canDel;
}
Vec2 Enemy::getPosition()
{
    return m_point;
}
Vec2 Enemy::getEnemyCenterPoint()
{
    return m_point + Vec2(0, m_height * 0.5);
}
Vec2 Enemy::getTargetPosition()
{
    return m_targetPoint;
}
void Enemy::dieingCall()
{
    m_status &= e_clear;
    m_status |= e_die;
}
void Enemy::diedCall()
{
//    m_status &= e_clear;
    m_status |= e_canDel;
}
void Enemy::hurtCall()
{
    m_status &= e_clear;
    m_status |= e_walk;
}
//void Enemy::hurtTanfeiCall()
//{
//    
//}
void Enemy::attackCall()
{
    switch (m_attackType) {
        case 1:     // 陆地 近程
            House::getInstance()->hurt(m_damage);
            break;
        case 2:     // 陆地 远程
        {
            BulletParameter bp(m_damage,
                               0,
                               1,
                               0,
                               0,
                               1,
                               100,
                               m_bulletSpeed,
                               0,
                               1,
                               t_house,
                               m_point - Vec2(m_width * 0.5, 0) + Vec2(0, m_health * 0.75),
                               m_targetPoint + Vec2(0,m_health * 0.7),
                               m_bulletModelId
                               );
            BulletManager::getInstance()->fire(bp);
            computeIfWander();
        }
            break;
        case 3:     // 陆地 自爆
            House::getInstance()->hurt(m_damage);
            dieingCall();
            break;
        case 4:     // 飞行 远程
        {
//            log("fei xing:%f",m_damage);
            m_status &= e_clear;
            m_status |= e_walk;
            BulletParameter bp(m_damage,
                               0,
                               1,
                               0,
                               0,
                               1,
                               100,
                               m_bulletSpeed,
                               0,
                               1,
                               t_house,
                               m_point - Vec2(m_width * 0.5, 0) + Vec2(0, m_health * 0.5),
                               m_targetPoint + Vec2(random(0, _G_M_M->flyEnemy_target_rightLine),
                                                    random(0, _G_M_M->flyEnemy_target_upLine)),
                               m_bulletModelId
                               );
            BulletManager::getInstance()->fire(bp);
        }
            break;
        default:
            break;
    }
}
// - 获得 基本 属性
string Enemy::getId()
{
    return m_id;
}
string Enemy::getMonsterName()
{
    return m_monsterName;
}
string Enemy::getModelId()
{
    return m_modelId;
}
string Enemy::getCapId()
{
    return m_capId;
}
int Enemy::getWidth()
{
    return m_width;
}
int Enemy::getHeight()
{
    return m_height;
}
int Enemy::getActionType()
{
    return m_actionType;
}
string Enemy::getBulletModelId()
{
    return m_bulletModelId;
}
int Enemy::getAttackType()
{
    return m_attackType;
}
float Enemy::getBulletSpeed()
{
    return m_bulletSpeed;
}
int Enemy::getLevel()
{
    return m_level;
}
int Enemy::getHealthValue()
{
    return m_health;
}
float Enemy::getHealthPercent()
{
    if (m_health < 0) {
        m_health = 0;
    }
    return m_health / m_totalHealth * 100.0f;
}
Vec2 Enemy::getSpeedV()
{
    return m_speedV;
}
float Enemy::getSpeedF()
{
    return m_speedF;
}
float Enemy::getDamage()
{
    return m_damage;
}
float Enemy::getAttackSpeed()
{
    return m_attackSpeed;
}
int Enemy::getGoldForDied()
{
    return m_gold;
}
string Enemy::getDrop()
{
    return m_drop;
}

