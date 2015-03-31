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



class GameDirector : public Node, public GameObject
{
private:
    
    
    
public:
    GameDirector();
    ~GameDirector();
    
    void gameLoop(float data);
};

#endif /* defined(__SwampAttack__GameDirector__) */
