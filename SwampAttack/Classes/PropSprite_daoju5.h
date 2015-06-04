//
//  PropSprite_daoju5.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/3.
//
//

#ifndef __SwampAttack__PropSprite_daoju5__
#define __SwampAttack__PropSprite_daoju5__

#include "PropSprite.h"

class PropSprite_daoju5 : public PropSprite {
private:
    
public:
    PropSprite_daoju5(string propId);
    void    throwProp();
    void    spriteCall(Node * psender);
    void    spriteCall2(Node * psender);
};

#endif /* defined(__SwampAttack__PropSprite_daoju5__) */
