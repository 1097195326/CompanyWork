//
//  GameScrollHeadler.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/7.
//
//

#include "GameScrollHeadler.h"

GameScrollHeadler::GameScrollHeadler()
{
    Sprite * bg = Sprite::create(ImagePath("gunItemBg.png"));
    addChild(bg);
    
}
GameScrollHeadler::~GameScrollHeadler()
{
    
}