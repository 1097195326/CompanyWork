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


class EnemySprite :public Sprite {
private:
    Enemy * m_model = NULL;
    
    std::map<std::string, Action *> m_map;
private:
    void    move();
    void    hurt();
    void    attack();
    
    void    hurtCall();
    void    attackCall();
public:
    EnemySprite(string name);
    virtual     ~EnemySprite();
    void        update(float data);
public:
    void    setMode(Enemy * model);
    

    
};

#endif /* defined(__SwampAttack__EnemySprite__) */
