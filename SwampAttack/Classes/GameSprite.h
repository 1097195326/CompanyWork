//
//  GameSprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/10.
//
//

#ifndef __SwampAttack__GameSprite__
#define __SwampAttack__GameSprite__

#include "BaseCode.h"

class GameSprite : public Sprite
{
private:
    EventListenerTouchOneByOne * m_listener;
    bool    m_isTouchMe;
    
public:
    GameSprite(std::string name);
    ~GameSprite();
    
    virtual bool    touchBegan(Touch * touch, Event * event);
    virtual void    touchMoved(Touch * touch, Event * event);
    virtual void    touchEnd(Touch * touch, Event * event);
    
    typedef std::function<void (Touch *, Event *)> TouchMeCall;
    TouchMeCall m_touchMeCall;
    void    setCanSwallowTouches(bool can);
    
};

#endif /* defined(__SwampAttack__GameSprite__) */
