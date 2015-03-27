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


class EnemySprite :public Sprite {
private:
    Action * m_walkAction;
    Action * m_hurtAction;
    
    std::map<std::string, Action *> m_map;
    
public:
    CREATE_FUNC(EnemySprite);
    bool init();
    EnemySprite();
    virtual ~EnemySprite();
    
    void createActionsWithFileName(const std::string &name);
    
public:
    virtual void move();
    virtual void hurt();
    
};

#endif /* defined(__SwampAttack__EnemySprite__) */
