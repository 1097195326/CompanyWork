//
//  ShopExpendShowLayer.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/23.
//
//

#ifndef __SwampAttack__ShopExpendShowLayer__
#define __SwampAttack__ShopExpendShowLayer__

#include "BaseCode.h"
#include "GameShopScene.h"

class ShopExpendShowLayer : public Layer {
private:
    EventListenerTouchOneByOne * m_listener;
    
    Sprite * bg;
    LayerColor * layerColor;
    Vec2    m_point;
    GameShopScene * m_shopLayer;
    
public:
    ShopExpendShowLayer(Vec2 position);
    ~ShopExpendShowLayer();
    void    setShopSceneLayer(GameShopScene * m_shopLayer);
    
    
    bool    touchBegan(Touch * touch, Event * event);
    void    touchEnd(Touch * touch, Event * event);
    
    void    touchItemEnd(Touch * touch, Event * event);
    void    actionEndCall();
};


#endif /* defined(__SwampAttack__ShopExpendShowLayer__) */
