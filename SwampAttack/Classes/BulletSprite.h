//
//  BulletSprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#ifndef __SwampAttack__BulletSprite__
#define __SwampAttack__BulletSprite__

#include "BaseCode.h"


class BulletSprite : public Sprite {
private:
    
public:
    BulletSprite();
    ~BulletSprite();
    
    CREATE_FUNC(BulletSprite);
    
    bool    init();
    
};

#endif /* defined(__SwampAttack__BulletSprite__) */
