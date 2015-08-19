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
#include "UserDelegatLayer.h"

class Gun;


class GameShopScene : public UserDelegateLayer,public GameScrollHeadlerTargetInterface
{
private:
    std::vector< GameVerticalScrollHeadlerView * >m_scrollViews;
//    GameVerticalScrollHeadlerView * m_scrollView;
    Sprite  * m_bg2;
    
private:
    void    visibelItemBg(int index);
    void    setItemBgSprite();
    void    setGunIcon();
    void    initShopView();
    void    initScrollView();
public:
    CREATE_SCENE_FUNC(GameShopScene);
//    static Scene * scene();
    CREATE_FUNC(GameShopScene);
    ~GameShopScene();
    virtual bool    init();
    
    void    updateData();
    GameScrollHeadler * getHeadlerByIndex(int index,int viewTag);
    
    
    void    homeButtonFunc(Ref * pSender);
    void    backButtonFunc(Ref * pSender);
public:
    
    Sprite  * m_gunItembgSprite;
    Sprite  * m_propItembgSprite;
    
};

#endif /* defined(__SwampAttack__GameShopScene__) */
