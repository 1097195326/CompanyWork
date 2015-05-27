//
//  ShopBuildingItemScrollHeadler.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/27.
//
//

#ifndef __SwampAttack__ShopBuildingItemScrollHeadler__
#define __SwampAttack__ShopBuildingItemScrollHeadler__

#include "GameScrollHeadler.h"
#include "ProgressBar.h"
#include "GameShopScene.h"


class ShopBuildingItemScrollHeadler : public GameScrollHeadler {
private:
    Label   *   m_buyLabel;
    Label   *   m_upgradeLabel;
    Label   *   m_bulletsLabel;
    
    ProgressBar *   m_progressBar;
    
    MenuItemImage * m_upGradeButton;
    MenuItemImage * m_unLockButton;
    MenuItemImage * m_buyButton;
    
    GameShopScene * m_shopScene;
private:
    void    initDefenseView();
    void    updateDefenseView();
    
    void    upGrade(Ref * pSender);
    void    unLock(Ref * pSender);
    void    buy(Ref * pSender);
public:
    void    setGameShopScene(GameShopScene * shopScene);
    ShopBuildingItemScrollHeadler(int index);
    ~ShopBuildingItemScrollHeadler();
    
};

#endif /* defined(__SwampAttack__ShopBuildingItemScrollHeadler__) */
