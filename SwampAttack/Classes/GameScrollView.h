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
private:
    ScrollController * m_scrollController;
    Layer   *   m_layer;
    float       m_viewWidth;
    float       m_viewHeight;
    EventListenerTouchOneByOne * m_listener;
public:
    void    setScrollControllerContentWidth(float width);
    void    setScrollControllerContentHeight(float height);
    void    addChildToScrollView(Node * node, int zOrder = 1);
    
public:
    GameScrollView(float width, float height);
    ~GameScrollView();
    void    update(float data);
    bool    touchBegan(Touch * touch, Event * event);
    void    touchMoved(Touch * touch, Event * event);
    void    touchEnd(Touch * touch, Event * event);
    
};

#endif /* defined(__SwampAttack__GameScrollView__) */
