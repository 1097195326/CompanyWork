//
//  EnemyGroup.h
//  SwampAttack
//
//  Created by oceantech02 on 15/4/7.
//
//

#ifndef __SwampAttack__EnemyGroup__
#define __SwampAttack__EnemyGroup__

#include "GameObject.h"
#include "Enemy.h"
#include "json/json.h"


enum EnemyGroupStatus{
    isHave,
    isDie
};
class EnemyGroup : public GameObject {
private:
    EnemyGroupStatus status;
    std::map<int,Enemy*> enemyData;
    
    int index[10];
public:
    EnemyGroup(Json::Value data);
    ~EnemyGroup();
    
public:
    void    setData(Json::Value data);
    void    clearData();
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__EnemyGroup__) */
