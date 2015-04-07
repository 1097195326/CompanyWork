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
    Action  * m_walkAction;
    Action  * m_hurtAction;
    
    std::map<std::string, Action *>     m_map;
private:
    void    move();
    void    hurt();
public:
    CREATE_FUNC(EnemySprite);
    EnemySprite();
    virtual     ~EnemySprite();
    bool        init();
public:
    void    setMode(Enemy * model);
    void    createActionsWithFileName(const std::string &name);
    

    
};

#endif /* defined(__SwampAttack__EnemySprite__) */
