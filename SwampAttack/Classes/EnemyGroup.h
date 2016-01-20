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
    _isHave,
    _isDie
};
class EnemyGroup : public GameObject {
private:
    EnemyGroupStatus status;
    std::list<Enemy*> enemyData;
    std::list<Enemy*> addEnemyData;
    std::list<Enemy*> show_enemyData;
    
    int enemy_index;
    bool    isLastIndex;
    float   delay;
public:
    EnemyGroup(Json::Value data);
    ~EnemyGroup();
    
public:
    void    setData(Json::Value data);
    bool    isDie();
    std::list<Enemy*> getEnemyData();
    std::list<Enemy*> getShowEnemyData();
    
    void    clearData();
    void    pushEnemy(Json::Value data,Vec2 position);
    void    reliveGame();
    void    gameLoop(float data);
    void    stopGame();
    void    continueGame();
};

#endif /* defined(__SwampAttack__EnemyGroup__) */
