//
//  GameShopScene.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#ifndef __SwampAttack__GameShopScene__
#define __SwampAttack__GameShopScene__

#include "BaseCode.h"
#include "GameObserver.h"
#include "GameScrollHeadlerTargetInterface.h"
#include "GameVerticalScrollHeadlerView.h"


class GameShopScene : public cocos2d::LayerColor, public GameObserver,public GameScrollHeadlerTargetInterface
{
private:
    std::vector< GameVerticalScrollHeadlerView * >m_scrollViews;
    
public:
    CREATE_SCENE_FUNC(GameShopScene);
    CREATE_FUNC(GameShopScene);
    
    virtual bool    init();
    
    void    updateData();
    void    upGrade(Ref * pSender);
    GameScrollHeadler * getHeadlerByIndex(int index,int viewTag);
};

#endif /* defined(__SwampAttack__GameShopScene__) */
