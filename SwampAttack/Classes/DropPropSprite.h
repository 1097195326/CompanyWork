//
//  DropPropSprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/24.
//
//

#ifndef __SwampAttack__DropPropSprite__
#define __SwampAttack__DropPropSprite__

#include "Prop.h"

class DropPropSprite : public Sprite {
private:
    Prop *  m_prop;
    
    
public:
    DropPropSprite(Prop * prop);
    ~DropPropSprite();
};

#endif /* defined(__SwampAttack__DropPropSprite__) */
