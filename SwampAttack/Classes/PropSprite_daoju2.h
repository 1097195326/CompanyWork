//
//  PropSprite_daoju2.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/3.
//
//

#ifndef __SwampAttack__PropSprite_daoju2__
#define __SwampAttack__PropSprite_daoju2__

#include "PropSprite.h"

class PropSprite_daoju2 : public PropSprite {
private:
    
public:
    PropSprite_daoju2(string propId);
    void    throwProp();
    
    void    spriteCall(Node * psender);
    void    spriteCall2(Node * psender);
};

#endif /* defined(__SwampAttack__PropSprite_daoju2__) */
