//
//  GameObserver.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#include "GameObserver.h"

GameObserver::GameObserver()
{
    
}
GameObserver::~GameObserver()
{
    m_sub->detach(this);
}
