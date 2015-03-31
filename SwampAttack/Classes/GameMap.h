//
//  GameMap.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/30.
//
//

#ifndef __SwampAttack__GameMap__
#define __SwampAttack__GameMap__

#include "BaseCode.h"

class GameMap
{
private:
    Vec2 m_startPoint;
    Vec2 m_targetPoint;
    
public:
    GameMap();
    
    static GameMap * getInstance();
    Vec2 getStartPoint();
    Vec2 getTargetPoint();
    
};

#endif /* defined(__SwampAttack__GameMap__) */
