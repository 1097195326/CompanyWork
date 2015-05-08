//
//  ShopSelectMeumView.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#include "ShopSelectMeumView.h"


ShopSelectMenuView::ShopSelectMenuView(int num):SelectMenuView(num)
{
    
}
ShopSelectMenuView::~ShopSelectMenuView()
{
    
}

void ShopSelectMenuView::setNormalSprite(std::string name)
{
    for (int i = 1; i <= m_num; ++i) {
        m_normalSprites[i] = Sprite::create(name+".png");
    }
}
void ShopSelectMenuView::setSelectSprite(std::string name)
{
    
}