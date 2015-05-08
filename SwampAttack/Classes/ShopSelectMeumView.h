//
//  ShopSelectMeumView.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#ifndef __SwampAttack__ShopSelectMeumView__
#define __SwampAttack__ShopSelectMeumView__

#include "SelectMenuView.h"

class ShopSelectMenuView : public SelectMenuView {
private:
    
public:
    ShopSelectMenuView(int num);
    ~ShopSelectMenuView();
    void    setNormalSprite(std::string name);
    void    setSelectSprite(std::string name);
};

#endif /* defined(__SwampAttack__ShopSelectMeumView__) */
