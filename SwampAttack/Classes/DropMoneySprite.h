//
//  DropMoneySprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/24.
//
//

#ifndef __SwampAttack__DropMoneySprite__
#define __SwampAttack__DropMoneySprite__

#include "MoneyObject.h"

class DropMoneySprite : public Sprite {
private:
    MoneyObject *  m_money;
    
    
public:
    DropMoneySprite(MoneyObject * money);
    ~DropMoneySprite();
};

#endif /* defined(__SwampAttack__DropMoneySprite__) */
