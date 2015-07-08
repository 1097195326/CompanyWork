//
//  DropPropSprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/24.
//
//

#ifndef __SwampAttack__DropPropSprite__
#define __SwampAttack__DropPropSprite__

#include "Prop.h"

class DropPropSprite : public Sprite {
private:
    Prop *  m_prop;
    Sprite * m_icon;
    
    EventListenerTouchOneByOne * m_listener;
    
    virtual bool    touchBegan(Touch * touch, Event * event);
    virtual void    touchEnd(Touch * touch, Event * event);
    
    void    isTimeToEnd(float data);
    void    guangEnd(Node * pSender);
    void    moveEnd(Node * pSender);
    
public:
    DropPropSprite(Prop * prop, Vec2 point);
    ~DropPropSprite();
};

#endif /* defined(__SwampAttack__DropPropSprite__) */
