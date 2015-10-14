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
#include "GameSprite.h"

class ShopGunItemScrollHeadler : public GameScrollHeadler, public GameObserver {
private:
    GameSprite * m_upGradeButton;
    GameSprite * m_unLockButton;
    GameSprite * m_buyButton;
    GameSprite * m_iconBg;
    MenuItemImage * m_takeUpButton;
    
    ProgressBar *   m_progressBar;
    
    GameShopScene * m_shopScene;
    
    Label   *   m_buyLabel;
    Label   *   m_bulletsLabel;
    Label   *   m_upgradeLabel;
    Label   *   m_levelUpLabel;
private:
    void    initGunView();
    void    initUnlockGunView();
    void    initLockGunView();
    void    updateGunView();
    
    void    upGrade(Touch * touch, Event * event);
    void    unLock(Touch * touch, Event * event);
    void    buy(Touch * touch, Event * event);
    void    takeUp(Ref * pSender);
    void    showDiscView(Touch * touch, Event * event);
public:
    void    setGameShopScene(GameShopScene * shopScene);
    ShopGunItemScrollHeadler(int index);
    ~ShopGunItemScrollHeadler();
    
    void    setHealderSelect();
    void    guangEnd(Node * pSender);
    void    updateData();
    
};

#endif /* defined(__SwampAttack__ShopGunItemScrollHeadler__) */
