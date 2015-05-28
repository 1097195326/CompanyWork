//
//  ShopPropIcon.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/28.
//
//

#ifndef __SwampAttack__ShopPropIcon__
#define __SwampAttack__ShopPropIcon__

#include "BaseCode.h"
#include "Prop.h"
#include "GameObserver.h"


class ShopPropIcon : public Sprite, public GameObserver {
private:
    EventListenerTouchOneByOne * m_listener;
    Sprite *    m_iconBg;
    Prop    *   m_prop = NULL;
    Sprite  *   m_icon;
    Label   *   m_num;
private:
    
    bool    touchBegan(Touch * touch, Event * event);
    void    touchEnd(Touch * touch, Event * event);
    
public:
    ShopPropIcon(int index);
    ~ShopPropIcon();
    void    updateData();
    void    reSetIcon(Prop * prop);
    
};

#endif /* defined(__SwampAttack__ShopPropIcon__) */
