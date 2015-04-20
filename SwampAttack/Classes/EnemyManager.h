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
#include "EnemyGroup.h"
#include "json/json.h"


class EnemyManager : public GameObject {
private:
    std::map<int,EnemyGroup *>   m_map;
    EnemyGroup * currentGroup;
    int     currentIndex;
    
public:
    EnemyManager();
    ~EnemyManager();
public:
    static EnemyManager * getInstance();
    void    setData(Json::Value data);
    void    clearData();
    
    void    gameLoop(float data);
    
    EnemyGroup * getCurrectGroup();
};
#endif /* defined(__SwampAttack__EnemyManager__) */
