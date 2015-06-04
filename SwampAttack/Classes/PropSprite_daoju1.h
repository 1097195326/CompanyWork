//
//  PropSprite_daoju1.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/3.
//
//

#ifndef __SwampAttack__PropSprite_daoju1__
#define __SwampAttack__PropSprite_daoju1__

#include "PropSprite.h"

class PropSprite_daoju1 : public PropSprite {
private:
    
public:
    PropSprite_daoju1(string propId);
    void    throwProp();
    void    spriteCall(Node * psender);
    void    spriteCall2(Node * psender);
};

#endif /* defined(__SwampAttack__PropSprite_daoju1__) */
