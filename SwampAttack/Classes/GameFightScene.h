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


class GameFightScene : public cocos2d::Layer
{
private:
    
    
public:
    CREATE_SCENE_FUNC(GameFightScene);
    CREATE_FUNC(GameFightScene);
    
    virtual bool    init();
    
    bool    touchBegan(Touch * touch, Event * event);
    void    touchMoved(Touch * touch, Event * event);
    void    touchEnd(Touch * touch, Event * event);
};

#endif /* defined(__SwampAttack__GameFightScene__) */
