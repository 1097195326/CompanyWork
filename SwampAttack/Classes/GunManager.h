//
//  GunManager.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/30.
//
//

#ifndef __SwampAttack__GunManager__
#define __SwampAttack__GunManager__

#include "GameObject.h"
#include "Gun.h"

class ShopGunIcon;

class GunManager : public GameObject {
private:
    std::map<string,Gun *> m_gunData;
    std::map<int,std::string> m_hashHead;
    
    std::map<string,Gun *> m_takeUpGunData;
    
    Gun *   currentGun;
    std::vector<ShopGunIcon *>   m_GunIcons;
private:
    
    
public:
    Gun *   getCurrentGun();
    void    addGun(string gunId);
    void    changeGun(string gunId);
    Gun *   getGunByIndex(int index);
    int     getGunNum();
    
    int     getTakeUpGunNum();
    Gun *   getTakeUpGunByIndex(int index);
    int     getTakeUpGunIndexByName(string name);
    void    takeUpGun(string gunId);
    void    takeDownGun(string gunId);
    
    void    setFightView();
    void    setShopView(Sprite * shopScene);
    
public:
    static GunManager * getInstance();
    GunManager();
    ~GunManager();
    void    gameLoop(float data);
    
};

#endif /* defined(__SwampAttack__GunManager__) */
