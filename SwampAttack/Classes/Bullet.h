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
enum BulletTarget
{
    t_enemy,
    t_house,
};
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
    BulletTarget m_target;      // 射击 对象
    Vec2    m_startPoint;       // 起始点
    Vec2    m_targetPoint;        // 目标点
    BulletParameter(int damage,
                    float damageArea,
                    int num,
                    float critRate,
                    float critDamageRate,
                    float accuracy,
                    float range,
                    float bulletSpeed,
                    BulletTarget target,
                    Vec2    startPoint,
                    Vec2    targetPoint
                    ):
    m_damage(damage),
    m_damageArea(damageArea),
    m_num(num),
    m_critRate(critRate),
    m_critDamageRate(critDamageRate),
    m_accuracy(accuracy),
    m_range(range),
    m_bulletSpeed(bulletSpeed),
    m_target(target),
    m_startPoint(startPoint),
    m_targetPoint(targetPoint)
    {}
};

enum BulletState
{
    _b_moving,
    _b_arrive,
    _b_die,
    _b_canDelete,
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
    int     getDamage();
    bool    isMoving();
    bool    isArrive();
    bool    isDie();
    void    arriveCall();
    void    setCanDelete();
    bool    isCanDelete();
    
public:
    Bullet(BulletParameter bp);
    ~Bullet();
    
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__Bullet__) */
