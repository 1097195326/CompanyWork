//
//  GameMapManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/14.
//
//

#include "GameMapManager.h"


GameMapManager * GameMapManager::getInstance()
{
    static GameMapManager manager;
    manager.getGameMap();
    return &manager;
}
GameMap * GameMapManager::getGameMap()
{
   static GameMap * gameMap = NULL ;
    if (gameMap)
    {
        return gameMap;
    }
    if (m_winSize.width == 1136)
    {
        gameMap = new GameMap5s();
    }else if(m_winSize.width  > 1136)
    {
        gameMap = new GameMap5s();
    }
    else
    {
        gameMap = new GameMap5s();
    }
    
    return gameMap;
}