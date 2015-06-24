//
//  DropPropSprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/24.
//
//

#include "DropPropSprite.h"
#include "GameFightScene.h"


DropPropSprite::DropPropSprite(Prop * prop)
{
    init();
    m_prop = prop;
    string modelId = m_prop->getModelId();
    
    Sprite * iconSpr = Sprite::create(ImagePath(StringUtils::format("%s_icon.png",modelId.c_str())));
    iconSpr->setScale(0.5);
    addChild(iconSpr);
    
    _G_V->addChild(this);
}
DropPropSprite::~DropPropSprite()
{
    
}