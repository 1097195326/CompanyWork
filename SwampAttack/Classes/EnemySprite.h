//
//  EnemySprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#ifndef __SwampAttack__EnemySprite__
#define __SwampAttack__EnemySprite__

#include "BaseCode.h"
#include "Enemy.h"

enum ActionStatus
{
    normal,
    isMoving,
    isHurting,
    isAttacking,
    isDieing,
};
class EnemySprite :public Sprite {
private:
    Enemy * m_model = NULL;
    ActionStatus    actionStatus = normal;
    std::map<std::string, Action *> m_map;
private:
    void    move();
    void    hurt();
    void    attack();
    void    die();
    
    void    hurtCall();
    void    attackCall();
    void    dieCall();
public:
    EnemySprite(string name);
    virtual     ~EnemySprite();
    void        update(float data);
public:
    void    setMode(Enemy * model);
    void    initDataWithName(string name);
    

    
};

#endif /* defined(__SwampAttack__EnemySprite__) */
