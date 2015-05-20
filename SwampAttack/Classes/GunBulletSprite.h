//
//  GunSprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/20.
//
//

#ifndef __SwampAttack__GunSprite__
#define __SwampAttack__GunSprite__

#include "BaseCode.h"
#include "Gun.h"
#include "GameObserver.h"

class GunBulletSprite : public Sprite,public GameObserver{
private:
    Gun * m_gun;
    std::vector<Sprite * > m_bullets;
    
public:
    GunBulletSprite(Gun * gun);
    void updateData();
};

#endif /* defined(__SwampAttack__GunSprite__) */
