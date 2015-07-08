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
    Sprite * m_icon;
    
    EventListenerTouchOneByOne * m_listener;
    
    virtual bool    touchBegan(Touch * touch, Event * event);
    virtual void    touchEnd(Touch * touch, Event * event);
    void    isTimeToEnd(float data);
    void    guangEnd(Node * pSender);
    void    moveEnd(Node * pSender);
public:
    DropMoneySprite(MoneyObject * money, Vec2 point);
    ~DropMoneySprite();
};

#endif /* defined(__SwampAttack__DropMoneySprite__) */
