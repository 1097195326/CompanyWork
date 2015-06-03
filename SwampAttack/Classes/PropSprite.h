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

enum PropSpriteState
{
    p_s_normal,
    p_s_arrve,
    p_s_throwing,
};

class PropSprite : public Sprite,public GameObserver{
protected:
    Prop * m_prop;
    Sprite  *   m_blueBg;
    Label   *   m_numLabel;
    EventListenerTouchOneByOne * m_listener;
    float   m_iconScale;
    Sprite  *   m_propIcon;
    Sprite  *   m_propTexiao;
    PropSpriteState m_state;
    
public:
    PropSprite(Prop * prop);
    ~PropSprite();
    virtual void    throwProp();
    void updateData();
    void update(float data);
    
    void    propArrveCall(Node * pSender);
    void    propThrowCall(Node * pSender);
    
    bool    touchBegan(Touch * touch, Event * event);
    void    touchMove(Touch * touch, Event * event);
    void    touchEnd(Touch * touch, Event * event);
};

#endif /* defined(__SwampAttack__PropSprite__) */
