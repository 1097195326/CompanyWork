//
//  GameShowDiscLayer.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/10.
//
//

#ifndef __SwampAttack__GameShowDiscLayer__
#define __SwampAttack__GameShowDiscLayer__

#include "BaseCode.h"

class GameShowDiscLayer : public Layer {
private:
    EventListenerTouchOneByOne * m_listener;
    
    Sprite * bg;
    LayerColor * layerColor;
    Vec2    m_point;
    
public:
    //    static Scene * scene(RenderTexture * rt);
    //    CREATE_FUNC(GamePauseScene);
    GameShowDiscLayer(std::string name,std::string disc,Vec2 position, bool isUnlock = false);
    ~GameShowDiscLayer();
    
//    void    continueGame(Ref * pSender);
    
    bool    touchBegan(Touch * touch, Event * event);
    void    touchEnd(Touch * touch, Event * event);
    void    actionEndCall();
    void    gotoShop(Ref * pSender);
};


#endif /* defined(__SwampAttack__GameShowDiscLayer__) */
