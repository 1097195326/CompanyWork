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

class Gun : public GameObject{
private:
    int     m_bullets;
    bool    m_isMaxLevel;
    bool    m_isUnlock;
    bool    m_isTakeUp;
private:
    
public:
    void    takeUp();
    void    takeDown();
    void    unlockGun();
    void    reloadBullet();
    void    fire(Vec2 position);
    
    
    bool    isTakeUp();
    bool    isUnlock();
    bool    isFull();
    bool    isHaveBullet();
    bool    isMaxLevel();
private:
    string  m_id;
    string  m_weaponName;           //  武器名称
    string  m_modelId;              //  模型编号
    string  m_bulletModelId;        //  子弹模型编号
    int     m_underAttackAction;    //  受击动作
    string  m_weaponType;           //  武器类型
    int     m_limitLevel;           //  强化等级上限
    float   m_damageArea;           //  伤害范围
    int     m_shrapnelNumber;       //  弹片数量
    float   m_critRate;             //  暴击率
    float   m_critDamageRate;       //  暴击伤害倍率
    float   m_accuracy;             //  精度
    float   m_fireRate;             //  射速
    float   m_range;                //  射程
    float   m_bulletSpeed;          //  弹道速度
    int     m_reloadType;           //  装填类型
    float   m_reloadSpeed;          //  装填速度
    float   m_switchSpeed;          //  切换武器速度
    int     m_ammunltionLimit;      //  弹药上限
    int     m_magazieSize;          //  弹夹容量
    int     m_bulletPrice;          //  弹药价格
    string  m_unlockMission;        //  解锁关卡
    int     m_unlockGold;           //  解锁价格
    string  m_weaponDescription;    //  武器描述
    //---- upgrade -----
    int     m_strengthenLevel;      //  强化等级
    float   m_damage;               //  伤害
    int     m_strengthenGold;       //  强化费用
    
public:
    //--- set function --
    void    addStrengthenLevel();
    void    buyBullet();
    //--- get function ---
    string  getWeaponName();
    int     getBulletNum();
    string  getModelId();
    string  getBulletModelId();
    int     getUnderAttackAction();
    int     getLimitLevel();
    int     getStrengthenLevel();
    int     getStrengthenGold();
    float   getDamage();
    float   getDamageArea();
    int     getShrapnelNumber();
    float   getCritRate();
    float   getCritDamageRate();
    float   getAccuracy();
    float   getFireRate();
    float   getRange();
    float   getBulletSpeed();
    int     getReloadType();
    float   getReloadSpeed();
    float   getSwitchSpeed();
    int     getAmmunltionLimit();
    int     getMagazieSize();
    int     getBulletPrice();
    string  getUnlockMission();
    int     getUnlockGold();
    string  getWeaponDescription();
    
public:
    Gun(Json::Value data);
    ~Gun();
    void    gameLoop(float data);
public:
    
};

#endif /* defined(__SwampAttack__Gun__) */
