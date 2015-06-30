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

class ShopSelectMenuView : public SelectMenuView{
private:
//    EventListenerTouchOneByOne * m_listener ;
public:
    ShopSelectMenuView(int num);
    ~ShopSelectMenuView();
    void    setNormalSprite(std::string name);
    void    setSelectSprite(std::string name);
    void    setIconSprite(std::string name);
    void    checkIndex();

//    bool    touchBegan(Touch * touch, Event * event);
    void    touchEnd(Touch * touch, Event * event);
    
    
};

#endif /* defined(__SwampAttack__ShopSelectMeumView__) */
