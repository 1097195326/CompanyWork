//
//  GameBuffManager.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/14.
//
//

#ifndef __SwampAttack__GameBuffManager__
#define __SwampAttack__GameBuffManager__

#include "GameBuff.h"
#include "GameObject.h"


#define _G_B_F GameBuffManager::getInstance()

class GameBuffManager : public GameObject{
private:
    std::list<GameBuff *>   m_buffData;
    float   m_dlay;
public:
    GameBuffManager();
    ~GameBuffManager();
    GameBuff * addBuff(string buffId);
    void    resetData();
    
    static GameBuffManager * getInstance();
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__GameBuffManager__) */
