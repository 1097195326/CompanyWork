//
//  GameDirector.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/30.
//
//

#include "GameDirector.h"


GameDirector::GameDirector()
{
    
    schedule(CC_SCHEDULE_SELECTOR(GameDirector::gameLoop), 1/60);
    
}
GameDirector::~GameDirector()
{
    
}
void GameDirector::gameLoop(float data)
{
    
}