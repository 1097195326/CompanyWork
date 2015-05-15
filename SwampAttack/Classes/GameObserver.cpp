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
    if (m_sub) {
        m_sub->detach(this);
    }
}
void GameObserver::setSubject(GameSubject *sub)
{
    m_sub = sub;
    m_sub->attach(this);
}