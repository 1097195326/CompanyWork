//
//  GameOverScene.h
//  SwampAttack
//
//  Created by 张洪星 on 15/6/1.
//
//

#ifndef __SwampAttack__GameOverScene__
#define __SwampAttack__GameOverScene__

#include "BaseCode.h"


class GameOverScene : public Layer {
private:
    GameOverStatus  m_overStatus;
    EventListenerTouchOneByOne * m_listener;
public:
    static Scene * scene(GameOverStatus status, RenderTexture * rt);
    GameOverScene(GameOverStatus status,RenderTexture * rt);
    ~GameOverScene();
    
    bool init();
    bool    touchBegan(Touch * touch, Event * event);
    
    void    nextGuanqia(Ref * pSender);
    void    restartGame(Ref * pSender);
    void    gotoMap(Ref * pSender);
};

#endif /* defined(__SwampAttack__GameOverScene__) */
