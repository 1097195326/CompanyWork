//
//  ShopPropItemScrollHeadler.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/27.
//
//

#ifndef __SwampAttack__ShopPropItemScrollHeadler__
#define __SwampAttack__ShopPropItemScrollHeadler__

#include "GameScrollHeadler.h"
#include "ProgressBar.h"
#include "GameShopScene.h"
#include "GameObserver.h"


class ShopPropItemScrollHeadler : public GameScrollHeadler , public GameObserver{
private:
    Label   *   m_buyLabel;
    Label   *   m_upgradeLabel;
    Label   *   m_bulletsLabel;
    Label   *   m_levelUpLabel;
    
    ProgressBar *   m_progressBar;
    
    MenuItemImage * m_upGradeButton;
    MenuItemImage * m_unLockButton;
    MenuItemImage * m_buyButton;
    MenuItemImage * m_takeUpButton;
    
    GameShopScene * m_shopScene;
private:
    void    initDaojuView();
    void    initUnlockView();
    void    initLockView();
    void    updateDaojuView();
    
    void    upGrade(Ref * pSender);
    void    unLock(Ref * pSender);
    void    buy(Ref * pSender);
    void    takeUp(Ref * pSender);
    void    showDiscView(Touch * touch, Event * event);
public:
    void    setGameShopScene(GameShopScene * shopScene);
    ShopPropItemScrollHeadler(int index);
    ~ShopPropItemScrollHeadler();
    
    void    updateData();
};

#endif /* defined(__SwampAttack__ShopPropItemScrollHeadler__) */
