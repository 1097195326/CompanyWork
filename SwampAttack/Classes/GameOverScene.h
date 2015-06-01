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

enum GameOverStatus
{
    o_win,
    o_loss,
};
class GameOverScene : public Layer {
private:
    GameOverStatus  m_overStatus;
public:
    static Scene * scene(GameOverStatus status);
    GameOverScene(GameOverStatus status);
    
    bool init();
    
    void    nextGuanqia(Ref * pSender);
    void    restartGame(Ref * pSender);
    void    gotoMap(Ref * pSender);
};

#endif /* defined(__SwampAttack__GameOverScene__) */
