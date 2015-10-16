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
#include "GameSprite.h"
#include "GameObserver.h"

class ShopBuildingItemScrollHeadler : public GameScrollHeadler,
public GameObserver{
private:
    Label   *   m_buyLabel;
    Label   *   m_upgradeLabel;
    Label   *   m_bulletsLabel;
    Label   *   m_levelUpLabel;
    
    ProgressBar *   m_progressBar;
    
    GameSprite * m_upGradeButton;
    GameSprite * m_unLockButton;
    GameSprite * m_buyButton;
    GameSprite * m_iconBg;
    GameShopScene * m_shopScene;
private:
    void    initDefenseView();
    void    updateDefenseView();
    
    void    upGrade(Touch * touch, Event * event);
    void    unLock(Touch * touch, Event * event);
    void    buy(Touch * touch, Event * event);
    void    showDiscView(Touch * touch, Event * event);

public:
    void    setGameShopScene(GameShopScene * shopScene);
    ShopBuildingItemScrollHeadler(int index);
    ~ShopBuildingItemScrollHeadler();
    
    void    setHealderSelect();
    void    guangEnd(cocos2d::Node *pSender);
    void    updateData();
};

#endif /* defined(__SwampAttack__ShopBuildingItemScrollHeadler__) */
