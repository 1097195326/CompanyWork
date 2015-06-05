//
//  PropSprite_daoju6.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/5.
//
//

#ifndef __SwampAttack__PropSprite_daoju6__
#define __SwampAttack__PropSprite_daoju6__

#include "PropSprite.h"

class PropSprite_daoju6 : public PropSprite {
private:
    
public:
    PropSprite_daoju6(string propId);
    void    throwProp();
    void    spriteCall(Node * psender);
    void    spriteCall2(Node * psender);
};

#endif /* defined(__SwampAttack__PropSprite_daoju6__) */
