//
//  shopGunIcon.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/27.
//
//

#ifndef __SwampAttack__shopGunIcon__
#define __SwampAttack__shopGunIcon__

#include "BaseCode.h"
#include "Gun.h"
#include "GameObserver.h"


class ShopGunIcon : public Sprite, public GameObserver {
private:
    EventListenerTouchOneByOne * m_listener;
    Sprite *    m_iconBg;
    Gun     *   m_gun = NULL;
    Sprite  *   m_icon;
    Label   *   m_bullets;
private:
    
    bool    touchBegan(Touch * touch, Event * event);
    void    touchEnd(Touch * touch, Event * event);

public:
    ShopGunIcon(int index);
    ~ShopGunIcon();
    void    updateData();
    void    reSetIcon(Gun * gun);
    
};

#endif /* defined(__SwampAttack__shopGunIcon__) */
