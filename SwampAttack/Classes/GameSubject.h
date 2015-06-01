//
//  GameSubject.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#ifndef __SwampAttack__GameSubject__
#define __SwampAttack__GameSubject__

#include "GameObserver.h"
#include "BaseCode.h"

#include <stdlib.h>
//using namespace std;

class GameSubject {
protected:
    std::list<GameObserver * > m_list_Observers;
    std::map<std::string,GameObserver *> m_map_Observers;
public:
    void    attach(GameObserver * server);
    void    detach(GameObserver * server);
    void    attach(std::string name,GameObserver * server);
    void    detach(std::string name);
    void    notify();
    void    notifyByName(std::string name);
    
public:
    GameSubject();
    virtual ~GameSubject();
};

#endif /* defined(__SwampAttack__GameSubject__) */
