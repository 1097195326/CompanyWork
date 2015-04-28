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
    bool    m_isOver;
public:
    static EnemyManager * getInstance();
    EnemyManager();
    ~EnemyManager();
    void    gameLoop(float data);
public:
    
    void    setData(Json::Value data);
    void    clearData();
    bool    isOver();
    
    
    EnemyGroup * getCurrectGroup();
};
#endif /* defined(__SwampAttack__EnemyManager__) */
