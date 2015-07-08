//
//  GameScrollView.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/6.
//
//

#ifndef __SwampAttack__GameScrollView__
#define __SwampAttack__GameScrollView__

#include "BaseCode.h"
#include "ScrollController.h"


class GameScrollView : public ClippingNode {
protected:
    ScrollController * m_scrollController;
    Layer   *   m_layer;
//    Sprite   *   m_layer;
    float       m_viewWidth;
    float       m_viewHeight;
    float       m_scrollContentWidth;
    float       m_scrollContentHeight;
    Vec2        m_moveV;
    bool        m_isMove;
private:
    EventListenerTouchOneByOne * m_listener;
public:
    void    setScrollControllerContentWidth(float width);
    void    setScrollControllerContentHeight(float height);
    void    setScrollHorizontal(bool canH);
    void    setScrollVertical(bool canV);
    void    setScrollUndulate(bool undulate);
    void    addChildToScrollView(Node * node, int zOrder = 1);
    void    removeAllChildFromScrollView();
public:
    GameScrollView(float width, float height);
    virtual ~GameScrollView();
    void    update(float data);
    bool    touchBegan(Touch * touch, Event * event);
    void    touchMoved(Touch * touch, Event * event);
    void    touchEnd(Touch * touch, Event * event);
    
};

#endif /* defined(__SwampAttack__GameScrollView__) */
