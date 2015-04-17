//
//  Bullet.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#ifndef __SwampAttack__Bullet__
#define __SwampAttack__Bullet__

#include "BaseCode.h"
#include "GameObject.h"

struct BulletParameter
{
    int     m_damage;         // 伤害
    float   m_damageArea;     // 伤害范围
    int     m_num;            // 弹片数量
    float   m_critRate;       // 暴击率
    float   m_critDamageRate; // 暴击伤害倍率
    float   m_accuracy;       // 精度
    float   m_range;          // 射程
    float   m_bulletSpeed;    // 弹道速度
    
    BulletParameter(int damage,
                    float damageArea,
                    int num,
                    float critRate,
                    float critDamageRate,
                    float accuracy,
                    float range,
                    float bulletSpeed):
    m_damage(damage),
    m_damageArea(damageArea),
    m_num(num),
    m_critRate(critRate),
    m_critDamageRate(critDamageRate),
    m_accuracy(accuracy),
    m_range(range),
    m_bulletSpeed(bulletSpeed){}
};

enum BulletState
{
    _b_moving,
    _b_arrive,
    _b_die,
};

class Bullet : public GameObject {
private:
    BulletParameter m_bp;
    Vec2    m_StartPoint;
    Vec2    m_Point;
    Vec2    m_toPoint;
    Vec2    m_speed;
    float   m_angle;
    
    BulletState m_state;
    
private:
    void    setView();
    
public:
    Vec2    getPosition();
    bool    isMoving();
    bool    isArrive();
    bool    isDie();
    void    arriveCall();
    
public:
    Bullet(BulletParameter bp, Vec2 fireToPosition);
    ~Bullet();
    
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__Bullet__) */
