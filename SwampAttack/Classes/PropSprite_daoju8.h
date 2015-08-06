//
//  PropSprite_daoju8.h
//  SwampAttack
//
//  Created by oceantech02 on 15/8/5.
//
//

#ifndef __SwampAttack__PropSprite_daoju8__
#define __SwampAttack__PropSprite_daoju8__

#include "PropSprite.h"

class PropSprite_daoju8 : public PropSprite {
private:
    
public:
    PropSprite_daoju8(string propId);
    void    throwProp();
    void    spriteCall(Node * psender);
    void    spriteCall2(Node * psender);
    void    spriteCall3(Node * psender);
};


#endif /* defined(__SwampAttack__PropSprite_daoju8__) */
