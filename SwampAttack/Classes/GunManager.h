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


class GunManager : public GameObject {
private:
    std::map<int,Gun *> m_gunData;
public:
    static GunManager * getInstance();
    GunManager();
    ~GunManager();
    
    void    gameLoop(float data);
    
};

#endif /* defined(__SwampAttack__GunManager__) */
