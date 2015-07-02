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
    Vec2 enemy_start_buttomPoint = {m_visibleOrigin.x + m_visibleSize.width + 70, m_visibleOrigin.y + 50};
    int enemy_target_upline = 60;
    Vec2 enemy_target_buttomPoint = {m_visibleOrigin.x + 250, m_visibleOrigin.y + 50};
    
    int flyEnemy_start_upline = 100;
    Vec2 flyEnemy_start_buttomPoint = {m_visibleOrigin.x + m_visibleSize.width + 70, m_visibleOrigin.y + 250};
    
    int flyEnemy_target_upLine = 250;
    int flyEnemy_target_rightLine = 150;
    Vec2 flyEnemy_target_buttomPoint = {m_visibleOrigin.x + 30, m_visibleOrigin.y + 80};
    
    
    Vec2 m_BulletStartPoint = {m_visibleOrigin.x + 230, m_visibleOrigin.y + 240};
    Vec2 gangpao_BulletStartPoint = {m_visibleOrigin.x + 150, m_visibleOrigin.y + 320};
    
    Vec2 fightScene_human_Point = {m_visibleOrigin.x + 200, m_visibleOrigin.y + 150};
    Vec2 fightScene_gangpao_Point = {m_visibleOrigin.x + 110,m_visibleOrigin.y + 340};
    
    Vec2 fightScene_zhalan_point1 = {m_visibleOrigin.x + 320,m_visibleOrigin.y + 70};
    Vec2 fightScene_zhalan_point2 = {m_visibleOrigin.x + 340,m_visibleOrigin.y + 150};
    float fightScene_zhalan_line = m_visibleOrigin.x + 330;
    
    Vec2 fightScene_HouseSprite_Position = {m_visibleOrigin.x + 150 ,m_visibleOrigin.y + 240};
    Vec2 fightScene_HouseBar_Position = {m_visibleOrigin.x + 300 ,m_visibleOrigin.y + m_visibleSize.height - 50};
    Vec2 fightScene_Gold_Position = {m_visibleOrigin.x + 40 ,m_visibleOrigin.y + m_visibleSize.height - 130};
    Vec2 fightScene_EnemyBar_Position = {m_visibleOrigin.x + m_visibleSize.width - 230 , m_visibleOrigin.y + m_visibleSize.height - 50};
    
    Vec2 fightScene_Bullet_Position = {m_visibleOrigin.x +510 ,m_visibleOrigin.y + m_visibleSize.height - 100};
    Vec2 fightScene_gunIcon_Position = {m_visibleOrigin.x +40 ,m_visibleOrigin.y + 50};
    
    Vec2 fightScene_PropIcon_Position = {m_visibleOrigin.x + m_visibleSize.width -60,m_visibleOrigin.y + m_visibleSize.height - 120};
    
    float fightScene_PropArrve_line = m_visibleOrigin.y + 120;
    
};

#endif /* defined(__SwampAttack__GameMap__) */
