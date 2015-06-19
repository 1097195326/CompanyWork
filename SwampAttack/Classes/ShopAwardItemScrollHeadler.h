//
//  ShopAwardItemScrollHeadler.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/27.
//
//

#ifndef __SwampAttack__ShopAwardItemScrollHeadler__
#define __SwampAttack__ShopAwardItemScrollHeadler__

#include "GameScrollHeadler.h"
#include "ProgressBar.h"
#include "GameShopScene.h"


class ShopAwardItemScrollHeadler : public GameScrollHeadler {
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
    void    initAwardView();
    void    updateAwardView();
    
    void    buy(cocos2d::Touch *touch, cocos2d::Event *event);
    void    showDiscView(Touch * touch, Event * event);
public:
    void    setGameShopScene(GameShopScene * shopScene);
    ShopAwardItemScrollHeadler(int index);
    ~ShopAwardItemScrollHeadler();
    
};

#endif /* defined(__SwampAttack__ShopAwardItemScrollHeadler__) */
