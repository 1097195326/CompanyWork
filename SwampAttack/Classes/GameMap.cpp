//
//  GameMap.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/30.
//
//

#include "GameMap.h"


GameMap::GameMap()
{
    m_startPoint = {visibleOrigin.x + visibleSize.width,10};
    m_targetPoint = {visibleOrigin.x + 20,visibleOrigin.y + 20};
}
GameMap * GameMap::getInstance()
{
    static GameMap _gameMap;
    return &_gameMap;
}
Vec2 GameMap::getStartPoint()
{
    return m_startPoint;
}
Vec2 GameMap::getTargetPoint()
{
    return m_targetPoint;
}
