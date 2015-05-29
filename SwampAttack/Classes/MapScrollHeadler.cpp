//
//  MapScrollHeadler.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/29.
//
//

#include "MapScrollHeadler.h"


MapScrollHeadler::MapScrollHeadler(int sceneIndex)
{
    Sprite * bg = Sprite::create(ImagePath("map_scene1.png"));
//    bg->setPosition(0,0);
    
    addChild(bg);
}
MapScrollHeadler::~MapScrollHeadler()
{
    
}