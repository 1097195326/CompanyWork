//
//  GameUser.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#ifndef __SwampAttack__GameUser__
#define __SwampAttack__GameUser__

#include "BaseCode.h"
#include "GameSubject.h"


#define _G_U GameUser::getInstance()
using namespace std;

class GameUser : public GameSubject {
private:
    UserDefault * m_user;
private:
    GameUser();
    ~GameUser();
    
    void    setBoolForKey(string name,bool value);
    void    setIntForKey(string name,int value);
    void    setFloatForKey(string name,float value);
    bool    getBoolForKey(string name);
    int     getIntForKey(string name);
    float   getFloatForKey(string name);
    
public:
    static GameUser * getInstance();
    //--- health ----
    int     getUserHealth();
    //---  gun ----
    void    unlockGun(string gunId);
    bool    isUnlockGun(string gunId);
    void    setGunDamage(string gunId, float damage);
    float   getGunDamage(string gunId);
    void    setGunBulletNumber(string bulletId,int num);
    int     getGunBulletNumber(string bulletId);
    //--- building ---
    
    //--- prop -----
    
    //--- award ----
    
    
};

#endif /* defined(__SwampAttack__GameUser__) */
