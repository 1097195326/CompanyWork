//
//  ShopGoldShowLayer.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/23.
//
//

#ifndef __SwampAttack__ShopGoldShowLayer__
#define __SwampAttack__ShopGoldShowLayer__

#include "BaseCode.h"
#include "GameShopScene.h"

class ShopGoldShowLayer : public Layer {
private:
    EventListenerTouchOneByOne * m_listener;
    
    Sprite * bg;
    LayerColor * layerColor;
    Vec2    m_point;
    GameShopScene * m_shopLayer;
    
public:
    ShopGoldShowLayer(Vec2 position);
    ~ShopGoldShowLayer();
    void    setShopSceneLayer(GameShopScene * m_shopLayer);
    
    
    bool    touchBegan(Touch * touch, Event * event);
    void    touchEnd(Touch * touch, Event * event);
    
    void    touchItemEnd(Touch * touch, Event * event);
    void    actionEndCall();
};


#endif /* defined(__SwampAttack__ShopGoldShowLayer__) */
