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
    p_s_hurting,
};

class PropSprite : public Sprite{
protected:
    Prop * m_prop;
    float   m_iconScale;
    Sprite  *   m_propIcon;
    Sprite  *   m_propTexiao;
    PropSpriteState m_state;
    
    
public:
    PropSprite(string propId);
    ~PropSprite();
    void    moveEnd();
    void    moveIng(Vec2 point);
    virtual void    throwProp();
    virtual void    readyToHurt();
    
    void update(float data);
    
    void    propArrveCall(Node * pSender);
    void    propThrowCall(Node * pSender);
    
};

#endif /* defined(__SwampAttack__PropSprite__) */
