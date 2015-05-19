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
    
    int enemy_start_upline = 100;
    Vec2 enemy_start_buttomPoint = {visibleOrigin.x + visibleSize.width, visibleOrigin.y + 50};
    int enemy_target_upling = 60;
    Vec2 enemy_target_buttomPoint = {visibleOrigin.x + 250, visibleOrigin.y + 50};
    
    Vec2 m_BulletStartPoint = {visibleOrigin.x + 230, visibleOrigin.y + 220};
    
    Vec2 fightScene_human_Point = {visibleOrigin.x + 200, visibleOrigin.y + 150};
    
    Vec2 fightScene_zhalan_point1 = {visibleOrigin.x + 320,visibleOrigin.y + 20};
    Vec2 fightScene_zhalan_point2 = {visibleOrigin.x + 340,visibleOrigin.y + 220};
    
    Vec2 fightScene_HouseSprite_Position = {visibleOrigin.x + 150 ,visibleOrigin.y + 250};
    Vec2 fightScene_HouseBar_Position = {visibleOrigin.x + 300 ,visibleOrigin.y + visibleSize.height - 50};
    
    
};

#endif /* defined(__SwampAttack__GameMap__) */
