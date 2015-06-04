//
//  BuffSprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/4.
//
//

#ifndef __SwampAttack__BuffSprite__
#define __SwampAttack__BuffSprite__
#include "BaseCode.h"

#include "GameBuff.h"


class BuffSprite : public Sprite {
private:
    GameBuff * m_buff;
    
    
public:
    BuffSprite(GameBuff * buff);
    
    void    update(float data);
};

#endif /* defined(__SwampAttack__BuffSprite__) */
