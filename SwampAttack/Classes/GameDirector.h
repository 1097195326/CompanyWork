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

#define _G_D GameDirector::getInstance()

enum GameDirectorStatus
{
    s_clear     = 0b00000000,
    s_stop      = 0b00000001,
    s_run       = 0b00000010,
    s_start     = 0b00000100,
    s_over      = 0b00001000,
    
};

class GameDirector : public Node, public GameObject
{
private:
    int     m_status = s_clear;
    GameMap * gameMap;
    
private:
    void    checkCross();
public:
    static GameDirector * getInstance();
    GameDirector();
    ~GameDirector();
public:
    void    initGameSingle();
    void    onTouchBegin(Touch * touch, Event * event);
    void    onTouchMove(Touch * touch, Event * event);
    void    onTouchEnd(Touch * touch, Event * event);
    void    startGame();
    void    restartGame();
    void    continueGame();
    void    stopGame();
    bool    isOver();
    void    clearStatus();
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__GameDirector__) */
