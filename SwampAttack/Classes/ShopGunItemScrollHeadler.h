//
//  ShopGunItemScrollHeadler.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/27.
//
//

#ifndef __SwampAttack__ShopGunItemScrollHeadler__
#define __SwampAttack__ShopGunItemScrollHeadler__

#include "GameScrollHeadler.h"
#include "ProgressBar.h"
#include "GameShopScene.h"
#include "GameObserver.h"


class ShopGunItemScrollHeadler : public GameScrollHeadler, public GameObserver {
private:
    Label   *   m_buyLabel;
    Label   *   m_upgradeLabel;
    Label   *   m_bulletsLabel;
    
    ProgressBar *   m_progressBar;
    
    MenuItemImage * m_upGradeButton;
    MenuItemImage * m_unLockButton;
    MenuItemImage * m_buyButton;
    MenuItemImage * m_takeUpButton;
    
    GameShopScene * m_shopScene;
private:
    void    initGunView();
    void    updateGunView();
    
    void    upGrade(Ref * pSender);
    void    unLock(Ref * pSender);
    void    buy(Ref * pSender);
    void    takeUp(Ref * pSender);
    void    showDiscView(Touch * touch, Event * event);
public:
    void    setGameShopScene(GameShopScene * shopScene);
    ShopGunItemScrollHeadler(int index);
    ~ShopGunItemScrollHeadler();
    
    void    updateData();
    
};

#endif /* defined(__SwampAttack__ShopGunItemScrollHeadler__) */
