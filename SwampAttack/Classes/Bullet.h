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
#include "BulletSprite.h"


class Bullet : public GameObject {
private:
    Vec2 m_speed;
    Vec2 m_point;
    
    
public:
    Bullet();
    ~Bullet();
    
    void gameLoop(float data);
};

#endif /* defined(__SwampAttack__Bullet__) */
