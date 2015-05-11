//
//  GameSubject.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#include "GameSubject.h"
#include "GameObserver.h"


GameSubject::GameSubject()
{
    
}
GameSubject::~GameSubject()
{
    if (m_list_Observers.size() > 0)
    {
        std::list<GameObserver *>::iterator iter;
        for (iter = m_list_Observers.begin(); iter != m_list_Observers.end(); ++iter)
        {
            GameObserver * server = * iter;
            detach(server);
        }
    }
    m_list_Observers.clear();
    
    if (m_map_Observers.size() > 0)
    {
        map<string,GameObserver *>::iterator iter;
        for (iter = m_map_Observers.begin(); iter != m_map_Observers.end(); ++iter)
        {
            string name = iter->first;
            detach(name);
        }
    }
}
void GameSubject::attach(GameObserver *server)
{
    m_list_Observers.push_front(server);
}
void GameSubject::attach(std::string name, GameObserver *server)
{
    m_map_Observers[name] = server;
}
void GameSubject::detach(GameObserver *server)
{
    if (server != NULL)
    {
        m_list_Observers.remove(server);
    }
}
void GameSubject::detach(std::string name)
{
    if (m_map_Observers[name]) {
        m_map_Observers.erase(name);
    }
}
void GameSubject::notify()
{
    std::list<GameObserver *>::iterator iter;
    for (iter = m_list_Observers.begin(); iter != m_list_Observers.end(); ++iter)
    {
        GameObserver * server = * iter;
        server->updateData();
    }
}
void GameSubject::notifyByName(std::string name)
{
    GameObserver * server = m_map_Observers[name];
    server->updateData();
}