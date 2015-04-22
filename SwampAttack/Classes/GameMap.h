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

class GameMap {
    
public:
    Vec2 m_startPoint = {visibleOrigin.x + visibleSize.width, visibleOrigin.y + 200};
    Vec2 m_targetPoint = {visibleOrigin.x + 200, visibleOrigin.y + 200};
    
    Vec2 m_BulletStartPoint = {visibleOrigin.x + 150, visibleOrigin.y + 270};
    
};

#endif /* defined(__SwampAttack__GameMap__) */
