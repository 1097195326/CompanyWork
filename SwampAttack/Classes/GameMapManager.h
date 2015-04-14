//
//  GameMapManager.h
//  SwampAttack
//
//  Created by oceantech02 on 15/4/14.
//
//

#ifndef __SwampAttack__GameMapManager__
#define __SwampAttack__GameMapManager__

#include "BaseCode.h"
#include "GameMap.h"
#include "GameMap6.h"
#include "GameMap5s.h"

class GameMapManager {
    
public:
    
    static GameMapManager * getInstance();
    GameMap * getGameMap();
};

#endif /* defined(__SwampAttack__GameMapManager__) */
