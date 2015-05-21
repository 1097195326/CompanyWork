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
    
public:
    static Scene * scene(RenderTexture * rt);
    CREATE_FUNC(GamePauseScene);
    
    bool init();
};

#endif /* defined(__SwampAttack__GamePauseScene__) */
