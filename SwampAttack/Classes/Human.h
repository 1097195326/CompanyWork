//
//  Human.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#ifndef __SwampAttack__Human__
#define __SwampAttack__Human__

#include "HumanSprite.h"
#include "GameObject.h"


class Human : public GameObject {
private:
    
public:
    Human();
    ~Human();
    
    void gameLoop(float data);
};

#endif /* defined(__SwampAttack__Human__) */
