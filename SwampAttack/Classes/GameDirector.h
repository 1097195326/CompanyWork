//
//  GameDirector.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/30.
//
//

#ifndef __SwampAttack__GameDirector__
#define __SwampAttack__GameDirector__

#include "BaseCode.h"
#include "GameObject.h"
#include "GameMapManager.h"


enum GameDirectorStatus
{
    s_clear   = 0b00000000,
    s_stop    = 0b00000001,
    s_run     = 0b00000010,
    
};

class GameDirector : public Node, public GameObject
{
private:
    int     m_status = s_clear;
    GameMap * gameMap;
    
    Layer * gameFightLayer;
public:
    static GameDirector * getInstance();
    GameDirector();
    ~GameDirector();
public:
    void    setGameLayer(Layer * layer);
    
    void    start();
    void    stop();
    void    clearStatus();
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__GameDirector__) */
