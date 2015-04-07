//
//  EnemyManager.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#ifndef __SwampAttack__EnemyManager__
#define __SwampAttack__EnemyManager__

#include <stdio.h>
#include <map>
#include "GameObject.h"


class EnemyManager : public GameObject {
    
public:
    std::map<int,int>   m_map;
    
    EnemyManager();
    ~EnemyManager();
    
    void gameLoop(float data);
    
};
#endif /* defined(__SwampAttack__EnemyManager__) */
