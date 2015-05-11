//
//  GameObserver.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#ifndef __SwampAttack__GameObserver__
#define __SwampAttack__GameObserver__

#include "GameSubject.h"


class GameObserver {
protected:
    GameSubject * m_sub;
    
public:
    virtual void    updateData() = 0;
    virtual void    setSubject(GameSubject * sub);
public:
    GameObserver();
    virtual ~GameObserver();
    
};

#endif /* defined(__SwampAttack__GameObserver__) */
