//
//  ShopHealthShowLayer.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/29.
//
//

#ifndef __SwampAttack__ShopHealthShowLayer__
#define __SwampAttack__ShopHealthShowLayer__

#include "BaseCode.h"
#include "GameShopScene.h"
#include "GameObserver.h"

class shopHealthShowLayer : public Layer ,public GameObserver {
private:
    EventListenerTouchOneByOne * m_listener;
    
    Sprite * bg;
    LayerColor * layerColor;
    Vec2    m_point;
    GameShopScene * m_shopLayer;
    std::vector<Sprite *> m_healthSprites;
    Label * m_timeLabel;
    
public:
    shopHealthShowLayer(Vec2 position);
    ~shopHealthShowLayer();
    void    setShopSceneLayer(GameShopScene * m_shopLayer);
    void    updateView();
    void    updateData();
    void    update(float data);
    
    
    bool    touchBegan(Touch * touch, Event * event);
    void    touchEnd(Touch * touch, Event * event);
    
    void    useToolToAddHealth(Touch * touch, Event * event);
    void    actionEndCall();
};


#endif /* defined(__SwampAttack__ShopHealthShowLayer__) */
