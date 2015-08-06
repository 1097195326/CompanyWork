//
//  PropSprite_daoju9.h
//  SwampAttack
//
//  Created by oceantech02 on 15/8/5.
//
//

#ifndef __SwampAttack__PropSprite_daoju9__
#define __SwampAttack__PropSprite_daoju9__

#include "PropSprite.h"

class PropSprite_daoju9 : public PropSprite {
private:
    
public:
    PropSprite_daoju9(string propId);
    void    throwProp();
    
    void    readyToHurt();
    
    void    canToHurt();
    
    void    hurtCall(Node * psender);
    void    spriteCall2(Node * psender);
    void    spriteCall3(Node * psender);
};

#endif /* defined(__SwampAttack__PropSprite_daoju9__) */
