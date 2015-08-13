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
#include "GameSubject.h"

#define defaultGunID "200003"

using namespace std;

struct GunActionData
{
    int attackFrame;
    int attackFrames;
    int changeFrames;
    int reloadFrames;
    int waitFrames;
};
class GunActionInfo {
private:
    std::map<string,GunActionData> m_infoData;
    GunActionInfo();
public:
    static GunActionInfo * getInstance();
    GunActionData getInfoByName(string name);
};
//-------
class Gun : public GameSubject{
private:
    int     m_bullets;
    int     m_totalBullets;
    bool    m_isMaxLevel;
    bool    m_isUnlock;
    bool    m_isTakeUp;
    bool    m_isDefaultGun;
    int     m_takeUpIndex;
    bool    m_isCurrentGun;
    
    float   m_fireWaitingTime;
    float   m_reloadWiatingTime;
private:
    
public:
    void    takeUp(int index);
    void    takeDown();
    bool    unlockGun();
    void    setIsCurrentGun(bool is);
    void    reloadBullet();
    bool    fire(Vec2 position);
    void    hurtEnemy();
    void    setFightView();
    
    bool    isDefaultGun();
    bool    isCurrentGun();
    bool    isTakeUp();
    bool    isUnlock();
    bool    isFull();
    bool    isHaveBullet();
    bool    isMaxLevel();
    
    int     getTakeUpIndex();
    void    checkUnlock(Layer * layer);
    void    resetData();
    void    saveBullet();
    
private:
    string  m_id;
    string  m_weaponName;           //  武器名称
    string  m_modelId;              //  模型编号
    string  m_bulletModelId;        //  子弹模型编号
    int     m_underAttackAction;    //  受击动作
    int     m_weaponType;           //  武器类型
    int     m_limitLevel;           //  强化等级上限
    float   m_damageArea;           //  伤害范围
    int     m_influence;            //  伤害怪物个数
    int     m_shrapnelNumber;       //  弹片数量
    int     m_bulletshow;
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
    bool    addStrengthenLevel();
    bool    buyBullet();
    void    addBullet(int num);
    float   getFireWaitingTime();
    float   getReloadWaitingTime();
    //--- get function ---
    string  getId();
    string  getWeaponName();
    int     getBulletNum();
    int     getTotalBulletNum();
    string  getModelId();
    string  getBulletModelId();
    int     getUnderAttackAction();
    int     getWeaponType();
    int     getLimitLevel();
    int     getStrengthenLevel();
    int     getStrengthenGold();
    float   getDamage();
    float   getDamageArea();
    int     getInfluence();
    int     getShrapnelNumber();
    int     getBulletshowType();
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
public:
    
};

#endif /* defined(__SwampAttack__Gun__) */
