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
#include "BulletModel.h"

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
    int     m_underAttackAction;// 受击动作
    int     m_hurtNum;
    BulletTarget m_target;      // 射击 对象
    Vec2    m_startPoint;       // 起始点
    Vec2    m_targetPoint;        // 目标点
    std::string m_modelId;
    BulletParameter(int damage,
                    float damageArea,
                    int num,
                    float critRate,
                    float critDamageRate,
                    float accuracy,
                    float range,
                    float bulletSpeed,
                    int underAttackAction,
                    int hurtNum,
                    BulletTarget target,
                    Vec2    startPoint,
                    Vec2    targetPoint,
                    std::string modelId
                    ):
    m_damage(damage),
    m_damageArea(damageArea),
    m_num(num),
    m_critRate(critRate),
    m_critDamageRate(critDamageRate),
    m_accuracy(accuracy),
    m_range(range),
    m_bulletSpeed(bulletSpeed),
    m_underAttackAction(underAttackAction),
    m_hurtNum(hurtNum),
    m_target(target),
    m_startPoint(startPoint),
    m_targetPoint(targetPoint),
    m_modelId(modelId)
    {}
};

enum BulletState
{
    _b_moving,
    _b_arrive,
    _b_die,
    _b_canDelete,
};

class Enemy;

struct BulletInfoData
{
    std::string name;
    int         frames;
};

class Bullet : public GameObject {
protected:
    BulletParameter m_bp;
    float   m_damage;
    Vec2    m_StartPoint;
    Vec2    m_Point;
    Vec2    m_toPoint;
    Vec2    m_speed;
    float   m_angle;
    float   m_effectDistance;
    
    BulletState m_state;
    Enemy   * m_enemy;
    BulletModel * m_bulletModel;
protected:
    
    
public:
    std::string getModelId();
    Vec2    getStartPosition();
    Vec2    getToPosition();
    Vec2    getPosition();
    Rect    getRect();
    int     getDamage();
    int     getAttackIndex();
    bool    isMoving();
    bool    isArrive();
    bool    isDie();
    void    arriveCall();
    void    setCanDelete();
    bool    isCanDelete();
    bool    isFireEnemy();
    bool    isFireHouse();
    
public:
    Bullet(BulletParameter bp);
    virtual ~Bullet();
    
    BulletInfoData getDandaoInfo();
    BulletInfoData getBaozhaTexiaoInfo();
    
    bool    isHaveExplode();
    
    virtual void    setView();
    
    void    gameLoop(float data);
    virtual void move();
};

#endif /* defined(__SwampAttack__Bullet__) */
