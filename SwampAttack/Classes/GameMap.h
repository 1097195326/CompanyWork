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
    int enemy_target_upline = 60;
    Vec2 enemy_target_buttomPoint = {visibleOrigin.x + 250, visibleOrigin.y + 50};
    
    int flyEnemy_start_upline = 100;
    Vec2 flyEnemy_start_buttomPoint = {visibleOrigin.x + visibleSize.width, visibleOrigin.y + 250};
    
    int flyEnemy_target_upLine = 250;
    int flyEnemy_target_rightLine = 150;
    Vec2 flyEnemy_target_buttomPoint = {visibleOrigin.x + 30, visibleOrigin.y + 80};
    
    
    Vec2 m_BulletStartPoint = {visibleOrigin.x + 230, visibleOrigin.y + 220};
    Vec2 gangpao_BulletStartPoint = {visibleOrigin.x + 150, visibleOrigin.y + 320};
    
    Vec2 fightScene_human_Point = {visibleOrigin.x + 200, visibleOrigin.y + 150};
    Vec2 fightScene_gangpao_Point = {visibleOrigin.x + 130,visibleOrigin.y + 320};
    
    Vec2 fightScene_zhalan_point1 = {visibleOrigin.x + 320,visibleOrigin.y + 70};
    Vec2 fightScene_zhalan_point2 = {visibleOrigin.x + 340,visibleOrigin.y + 150};
    float fightScene_zhalan_line = visibleOrigin.x + 330;
    
    Vec2 fightScene_HouseSprite_Position = {visibleOrigin.x + 150 ,visibleOrigin.y + 250};
    Vec2 fightScene_HouseBar_Position = {visibleOrigin.x + 300 ,visibleOrigin.y + visibleSize.height - 50};
    
    Vec2 fightScene_Bullet_Position = {visibleOrigin.x +510 ,visibleOrigin.y + visibleSize.height - 120};
    Vec2 fightScene_gunIcon_Position = {visibleOrigin.x +40 ,visibleOrigin.y + visibleSize.height - 140};
    
};

#endif /* defined(__SwampAttack__GameMap__) */
