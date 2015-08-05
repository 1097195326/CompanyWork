//
//  PropSprite_daoju7.h
//  SwampAttack
//
//  Created by oceantech02 on 15/8/5.
//
//

#ifndef __SwampAttack__PropSprite_daoju7__
#define __SwampAttack__PropSprite_daoju7__

#include "PropSprite.h"

class PropSprite_daoju7 : public PropSprite {
private:
    
public:
    PropSprite_daoju7(string propId);
    void    throwProp();
    void    spriteCall(Node * psender);
    void    spriteCall2(Node * psender);
};

#endif /* defined(__SwampAttack__PropSprite_daoju7__) */
