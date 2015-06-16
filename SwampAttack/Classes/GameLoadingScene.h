//
//  GameLoadingScene.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/16.
//
//

#ifndef __SwampAttack__GameLoadingScene__
#define __SwampAttack__GameLoadingScene__

#include "BaseCode.h"

class GameLoadingScene : public Layer {
private:
    std::string m_guanqiaId;
public:
    static Scene * scene(std::string guanqiaId);
    GameLoadingScene(std::string guanqiaId);
    ~GameLoadingScene();
    
    void    loadingData(float data);
    void    gotoFightScene(float data);
    
};

#endif /* defined(__SwampAttack__GameLoadingScene__) */
