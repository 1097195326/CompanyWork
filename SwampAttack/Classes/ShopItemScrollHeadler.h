//
//  ShopItemScrollHeadler.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/12.
//
//

#ifndef __SwampAttack__ShopItemScrollHeadler__
#define __SwampAttack__ShopItemScrollHeadler__

#include "GameScrollHeadler.h"

class ShopItemScrollHeadler : public GameScrollHeadler {
private:
    int     m_itemIndex;
    
    
public:
    
    ShopItemScrollHeadler(int index,int itemIndex);
    ~ShopItemScrollHeadler();
    
};

#endif /* defined(__SwampAttack__ShopItemScrollHeadler__) */
