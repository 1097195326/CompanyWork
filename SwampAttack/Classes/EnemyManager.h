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

class EnemyManager {
    
public:
    std::map<int,int>   m_map;
    
    EnemyManager();
    ~EnemyManager();
    
    
};
#endif /* defined(__SwampAttack__EnemyManager__) */
