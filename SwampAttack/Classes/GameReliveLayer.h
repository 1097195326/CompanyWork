//
//  GameReliveLayer.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/30.
//
//

#ifndef __SwampAttack__GameReliveLayer__
#define __SwampAttack__GameReliveLayer__

#include "BaseCode.h"
#include "GameFightScene.h"

class GameReliveLayer : public Layer {
private:
    EventListenerTouchOneByOne * m_listener;
    Label * m_timeLabel;
    int     m_time;
    GameFightScene * m_fightLayer;
public:
    GameReliveLayer(RenderTexture * rt);
    ~GameReliveLayer();
    void    setFightLayer(GameFightScene * layer);
    
    void    reliveGame();
    void    continueTimeToEnd();
    
    void    continueGame(Ref * pSender);
    void    updateTime(float data);
    
    bool    touchBegan(Touch * touch, Event * event);
};

#endif /* defined(__SwampAttack__GameReliveLayer__) */
