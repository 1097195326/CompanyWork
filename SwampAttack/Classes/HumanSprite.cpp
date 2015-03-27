//
//  HumanSprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/27.
//
//

#include "HumanSprite.h"


bool HumanSprite::init()
{
    if (!Sprite::init()) {
        return false;
    }
    
    return true;
}