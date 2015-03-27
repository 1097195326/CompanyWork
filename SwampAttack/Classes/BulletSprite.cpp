//
//  BulletSprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "BulletSprite.h"


BulletSprite::BulletSprite()
{
    
}
BulletSprite::~BulletSprite()
{
    
}
bool BulletSprite::init()
{
    if (!Sprite::init()) {
        return false;
    }
    
    return true;
}