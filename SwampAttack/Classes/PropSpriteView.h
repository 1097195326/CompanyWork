//
//  PropSpriteView.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/4.
//
//

#ifndef __SwampAttack__PropSpriteView__
#define __SwampAttack__PropSpriteView__

#include "BaseCode.h"
#include "Prop.h"
#include "GameObserver.h"
#include "PropSprite.h"

class PropSpriteView : public Sprite,public GameObserver{
protected:
    Prop * m_prop;
    Sprite  *   m_blueBg;
    PropSprite  *   m_propIcon;
    Label   *   m_numLabel;
    EventListenerTouchOneByOne * m_listener;
    float   m_iconScale;
    
    float   m_moveJuli;
    
public:
    PropSpriteView(Prop * prop);
    ~PropSpriteView();
    
    void updateData();
    
    bool    touchBegan(Touch * touch, Event * event);
    void    touchMove(Touch * touch, Event * event);
    void    touchEnd(Touch * touch, Event * event);
};

#endif /* defined(__SwampAttack__PropSpriteView__) */
