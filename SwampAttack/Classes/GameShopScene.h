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


class GameShopScene : public Layer, public GameObserver,public GameScrollHeadlerTargetInterface
{
private:
//    std::vector< GameVerticalScrollHeadlerView * >m_scrollViews;
    GameVerticalScrollHeadlerView * m_scrollView;
    std::vector<Sprite *> m_healthSprites;
    Label   * m_goldLabel;
public:
    CREATE_SCENE_FUNC(GameShopScene);
    CREATE_FUNC(GameShopScene);
    ~GameShopScene();
    virtual bool    init();
    
    void    updateData();
    GameScrollHeadler * getHeadlerByIndex(int index,int viewTag);
    
    
    void    homeButtonFunc(Ref * pSender);
    void    backButtonFunc(Ref * pSender);
public:
    void    updateGoldView();
};

#endif /* defined(__SwampAttack__GameShopScene__) */
