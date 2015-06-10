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
public:
    //    static Scene * scene(RenderTexture * rt);
    //    CREATE_FUNC(GamePauseScene);
    GameShowDiscLayer();
    ~GameShowDiscLayer();
    
//    void    continueGame(Ref * pSender);
    
    bool    touchBegan(Touch * touch, Event * event);
};


#endif /* defined(__SwampAttack__GameShowDiscLayer__) */
