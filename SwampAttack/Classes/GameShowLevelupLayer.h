//
//  GameShowLevelupLayer.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/10.
//
//

#ifndef __SwampAttack__GameShowLevelupLayer__
#define __SwampAttack__GameShowLevelupLayer__

#include "BaseCode.h"

class GameShowLevelupLayer : public Layer {
private:
    EventListenerTouchOneByOne * m_listener;
    
public:
    //    static Scene * scene(RenderTexture * rt);
    //    CREATE_FUNC(GamePauseScene);
    GameShowLevelupLayer(std::string name);
    ~GameShowLevelupLayer();
    
    void    addBackLayer(Node * pSender);
    void    timeIsEnd(Node * pSender);
    
    bool    touchBegan(Touch * touch, Event * event);
};


#endif /* defined(__SwampAttack__GameShowLevelupLayer__) */
