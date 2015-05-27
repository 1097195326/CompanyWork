//
//  ShopAwardItemScrollHeadler.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/27.
//
//

#include "ShopAwardItemScrollHeadler.h"

#include "GunManager.h"
#include "PropManager.h"
#include "DefenseBuildingManager.h"
#include "GameUser.h"


ShopAwardItemScrollHeadler::ShopAwardItemScrollHeadler(int index)
{
    setIndex(index);
    
    Sprite * itemBg = Sprite::create(ImagePath("shopItemBg1.png"));
    addChild(itemBg);
    
}
ShopAwardItemScrollHeadler::~ShopAwardItemScrollHeadler()
{
    //    log("shop item scroll headler remove");
}
void ShopAwardItemScrollHeadler::setGameShopScene(GameShopScene *shopScene)
{
    m_shopScene = shopScene;
}
void ShopAwardItemScrollHeadler::initDefenseView()
{
    removeAllChildrenWithCleanup(true);
    
    
    updateDefenseView();
}
void ShopAwardItemScrollHeadler::updateDefenseView()
{
    
}
void ShopAwardItemScrollHeadler::upGrade(Ref * pSender)
{
    
}
void ShopAwardItemScrollHeadler::unLock(Ref * pSender)
{
    
}
void ShopAwardItemScrollHeadler::buy(Ref * pSender)
{
    
}