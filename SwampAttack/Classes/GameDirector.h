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
#include "GameSubject.h"
#include "GameMapManager.h"


#define _G_D GameDirector::getInstance()

enum GameDirectorStatus
{
    s_clear     = 0b00000000,
    s_stop      = 0b00000001,
    s_run       = 0b00000010,
    s_over      = 0b00000100,
    
};

class GameDirector : public Node, public GameObject,public GameSubject
{
private:
    int     m_status = s_clear;
    GameMap * gameMap;
    GameOverStatus m_overStatus;
    int     m_goldNum;
private:
    void    checkCross();
public:
    static GameDirector * getInstance();
    GameDirector();
    ~GameDirector();
public:
    void    initGameView();
    void    onTouchBegin(Touch * touch, Event * event);
    void    onTouchMove(Touch * touch, Event * event);
    void    onTouchEnd(Touch * touch, Event * event);
    void    resetGameData();
    void    startGame();
    void    continueGame();
    void    stopGame();
    bool    isOver();
    GameOverStatus getOverStatus();
    void    clearStatus();
    void    addGold(int gold);
    int     getGoldNum();
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__GameDirector__) */
