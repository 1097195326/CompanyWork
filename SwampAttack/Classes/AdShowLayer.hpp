//
//  AdShowLayer.hpp
//  SwampAttack
//
//  Created by oceantech02 on 16/1/12.
//
//

#ifndef AdShowLayer_hpp
#define AdShowLayer_hpp

#include "BaseCode.h"


class AdShowLayer : public Layer {
private:
    EventListenerTouchOneByOne * m_listener;
    
    Sprite * bg;
    LayerColor * layerColor;
    Vec2    m_point;
    
public:
    AdShowLayer();
    ~AdShowLayer();
    
    bool    touchBegan(Touch * touch, Event * event);
    void    touchEnd(Touch * touch, Event * event);
    void    closeAd();
    
    void    actionEndCall();
};


#endif /* AdShowLayer_hpp */
