//
//  DropMoneySprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/24.
//
//

#include "DropMoneySprite.h"
#include "GameFightScene.h"


DropMoneySprite::DropMoneySprite(MoneyObject * money)
{
    init();
    m_money = money;
    string modelId = m_money->getModelId();
    
    Sprite * iconSpr = Sprite::create(ImagePath(StringUtils::format("%s_icon.png",modelId.c_str())));
    iconSpr->setScale(0.5);
    addChild(iconSpr);
    
    _G_V->addChild(this);
}
DropMoneySprite::~DropMoneySprite()
{
    
}