//
//  FireBulletSprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/7/29.
//
//

#ifndef __SwampAttack__FireBulletSprite__
#define __SwampAttack__FireBulletSprite__

#include "BaseCode.h"
#include "Bullet.h"


class FireBulletSprite : public Sprite {
private:
    Bullet * m_model;
    
public:
    void    setModel(Bullet * bullet);
public:
    FireBulletSprite();
    ~FireBulletSprite();
    
    CREATE_FUNC(FireBulletSprite);
    
    void    update(float data);
    
};

#endif /* defined(__SwampAttack__FireBulletSprite__) */
