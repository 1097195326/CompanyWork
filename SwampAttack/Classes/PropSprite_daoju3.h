//
//  PropSprite_daoju3.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/3.
//
//

#ifndef __SwampAttack__PropSprite_daoju3__
#define __SwampAttack__PropSprite_daoju3__

#include "PropSprite.h"

class PropSprite_daoju3 : public PropSprite {
private:
    
public:
    PropSprite_daoju3(string propId);
    void    throwProp();
    
    void    readyToHurt();
    
    void    canToHurt();
    
    void    hurtCall(Node * psender);
    void    spriteCall2(Node * psender);
};

#endif /* defined(__SwampAttack__PropSprite_daoju3__) */
