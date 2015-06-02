//
//  PropSprite.h
//  SwampAttack
//
//  Created by 张洪星 on 15/6/2.
//
//

#ifndef __SwampAttack__PropSprite__
#define __SwampAttack__PropSprite__

#include "BaseCode.h"
#include "Prop.h"
#include "GameObserver.h"

class PropSprite : public Sprite,public GameObserver{
private:
    Prop * m_prop;
    Sprite  *   m_blueBg;
    Label   *   m_numLabel;
    EventListenerTouchOneByOne * m_listener;
    float   m_iconScale;
    
public:
    PropSprite(Prop * prop);
    ~PropSprite();
    void updateData();
    
    bool    touchBegan(Touch * touch, Event * event);
    void    touchMove(Touch * touch, Event * event);
    void    touchEnd(Touch * touch, Event * event);
};

#endif /* defined(__SwampAttack__PropSprite__) */
