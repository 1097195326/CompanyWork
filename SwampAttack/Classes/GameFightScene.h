//
//  GameFightScene.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#ifndef __SwampAttack__GameFightScene__
#define __SwampAttack__GameFightScene__

#include "BaseCode.h"


class GameFightScene : public cocos2d::Layer {
private:
    
    
public:
    CREATE_SCENE_FUNC(GameFightScene);
    CREATE_FUNC(GameFightScene);
    
    virtual bool init();
};

#endif /* defined(__SwampAttack__GameFightScene__) */
