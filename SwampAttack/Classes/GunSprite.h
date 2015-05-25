//
//  GunSprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/20.
//
//

#ifndef __SwampAttack__GunSprite__
#define __SwampAttack__GunSprite__

#include "BaseCode.h"
#include "Gun.h"
#include "GameObserver.h"

class GunSprite : public Sprite,public GameObserver{
private:
    Gun * m_gun;
    std::vector<Sprite * > m_bullets;
    std::vector<Sprite * > m_bulletsBg;
    Sprite  *   m_greenBg;
    Sprite  *   m_blueBg;
    Label   *   m_bulletLabel;
    EventListenerTouchOneByOne * m_listener;
    float   m_iconScale;
    
public:
    GunSprite(Gun * gun);
    ~GunSprite();
    void updateData();
    
    bool    touchBegan(Touch * touch, Event * event);
    void    touchEnd(Touch * touch, Event * event);
};

#endif /* defined(__SwampAttack__GunSprite__) */
