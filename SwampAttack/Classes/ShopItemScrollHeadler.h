//
//  ShopItemScrollHeadler.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/12.
//
//

#ifndef __SwampAttack__ShopItemScrollHeadler__
#define __SwampAttack__ShopItemScrollHeadler__

#include "GameScrollHeadler.h"
#include "ProgressBar.h"


class ShopItemScrollHeadler : public GameScrollHeadler {
private:
    int     m_itemIndex;
    Label   *   m_buyLabel;
    Label   *   m_upgradeLabel;
    Label   *   m_bulletsLabel;
    
    ProgressBar *   m_progressBar;
    
    MenuItemImage * m_upGradeButton;
    MenuItemImage * m_unLockButton;
    MenuItemImage * m_buyButton;
    
    
private:
    void    initGunView();
    void    updateGunView();
    void    initDefenseView();
    void    updateDefenseView();
    void    initDaojuView();
    void    updateDaojuView();
    
    void    upGrade(Ref * pSender);
    void    unLock(Ref * pSender);
    void    buy(Ref * pSender);
public:
    
    ShopItemScrollHeadler(int index,int itemIndex);
    ~ShopItemScrollHeadler();
    
};

#endif /* defined(__SwampAttack__ShopItemScrollHeadler__) */
