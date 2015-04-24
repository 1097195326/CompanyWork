//
//  BulletSprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#ifndef __SwampAttack__BulletSprite__
#define __SwampAttack__BulletSprite__

#include "BaseCode.h"
#include "Bullet.h"


class BulletSprite : public Sprite {
private:
    Bullet * m_model;
public:
    void    setModel(Bullet * bullet);
public:
    BulletSprite();
    ~BulletSprite();
    
    CREATE_FUNC(BulletSprite);
    
    void    update(float data);
    
};

#endif /* defined(__SwampAttack__BulletSprite__) */
