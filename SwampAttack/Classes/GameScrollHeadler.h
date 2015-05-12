//
//  GameScrollHeadler.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/7.
//
//

#ifndef __SwampAttack__GameScrollHeadler__
#define __SwampAttack__GameScrollHeadler__

#include "BaseCode.h"


class GameScrollHeadler : public Node  {
protected:
    int     m_index;
    
public:
    GameScrollHeadler();
    ~GameScrollHeadler();
public:
    void    setIndex(int index);
    int     getIndex();
};

#endif /* defined(__SwampAttack__GameScrollHeadler__) */
