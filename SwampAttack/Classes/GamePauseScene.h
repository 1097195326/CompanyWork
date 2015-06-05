//
//  GamePauseScene.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/21.
//
//

#ifndef __SwampAttack__GamePauseScene__
#define __SwampAttack__GamePauseScene__

#include "BaseCode.h"

class GamePauseScene : public Layer {
private:
    EventListenerTouchOneByOne * m_listener;
public:
//    static Scene * scene(RenderTexture * rt);
//    CREATE_FUNC(GamePauseScene);
    GamePauseScene(RenderTexture * rt);
    ~GamePauseScene();
    
    void    continueGame(Ref * pSender);
    void    restartGame(Ref * pSender);
    void    gotoMap(Ref * pSender);
    
    bool    touchBegan(Touch * touch, Event * event);
};

#endif /* defined(__SwampAttack__GamePauseScene__) */
