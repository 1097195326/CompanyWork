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

#define defaultGunID "200001"

class GunManager : public GameObject {
private:
    std::map<string,Gun *> m_gunData;
    Gun *   currentGun;
private:
    
    
public:
    Gun *   getCurrentGun();
    void    addGun(string gunId);
    void    changeGun(string gunId);
    
public:
    static GunManager * getInstance();
    GunManager();
    ~GunManager();
    void    gameLoop(float data);
    
};

#endif /* defined(__SwampAttack__GunManager__) */
