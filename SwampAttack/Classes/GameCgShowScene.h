//
//  GameCgShowScene.h
//  SwampAttack
//
//  Created by oceantech02 on 15/8/10.
//
//

#ifndef __SwampAttack__GameCgShowScene__
#define __SwampAttack__GameCgShowScene__

#include "BaseCode.h"

class GameCgShowScene : public Layer {
private:
    
    int     m_index;
    Sprite  *   m_spr1;
    Sprite  *   m_spr2;
    Label   *   m_text;
    
    std::vector<std::string> cgText;
    
public:
    static Scene * scene();
    CREATE_FUNC(GameCgShowScene);
    ~GameCgShowScene();
    bool init();
    
    void    skipToHomeScene(Ref * pSender);
    void    updateCg(float data);
    void    swapEnd();
    
};

#endif /* defined(__SwampAttack__GameCgShowScene__) */
