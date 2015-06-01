//
//  GameObserver.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#include "GameObserver.h"
#include "GameSubject.h"


GameObserver::GameObserver()
{
    m_sub = NULL;
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
void GameObserver::detachSubject()
{
    if (m_sub) {
        m_sub->detach(this);
    }
}