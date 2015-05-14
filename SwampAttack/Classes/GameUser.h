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
    void    setStringForKey(string name,string value);
    bool    getBoolForKey(string name);
    int     getIntForKey(string name);
    float   getFloatForKey(string name);
    string  getStringForKey(string name);
    
public:
    static GameUser * getInstance();
    //--- health ----
    int     getUserHealth();
    void    setUserGold(int gold);
    int     getUserGold();
    //---  gun ----
    void    unlockGun(string gunId);
    bool    isUnlockGun(string gunId);
    void    setGunLevel(string gunId, int level);
    int     getGunLevel(string gunId);
    void    setGunBulletNumber(string gunId,int num);
    int     getGunBulletNumber(string gunId);
    //--- building ---
    void    unlockBuilding(string buildingId);
    bool    isUnlockBuilding(string buildingId);
    void    setBuildingLevel(string buildingId,int level);
    int     getBuildingLevel(string buildingId);
    //--- prop -----
    void    unlockProp(string propId);
    bool    isUnlockProp(string propId);
    void    setPorpNum(string propId,int num);
    int     getPropNum(string propId);
    //--- award ----
    
    
};

#endif /* defined(__SwampAttack__GameUser__) */
