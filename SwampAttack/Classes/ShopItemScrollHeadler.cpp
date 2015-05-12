//
//  ShopItemScrollHeadler.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/12.
//
//

#include "ShopItemScrollHeadler.h"
#include "GunManager.h"


ShopItemScrollHeadler::ShopItemScrollHeadler(int index,int itemIndex):m_itemIndex(itemIndex)
{
    setIndex(index);
    
    Sprite * itemBg;
    switch (m_itemIndex) {
        
        case 0 :
        {
            itemBg = Sprite::create(ImagePath("shopItemBg1.png"));
            addChild(itemBg);
            Sprite * iconBg = Sprite::create(ImagePath("shopItemIconBg.png"));
            iconBg->setPosition(iconBg->getContentSize().width * 0.75 - itemBg->getContentSize().width * 0.5, getPositionY());
            addChild(iconBg);
            Gun * gun = GunManager::getInstance()->getGunByIndex(m_index);
            string gunModelId = gun->getModelId();
            string gunIconStr = StringUtils::format("%s_icon.png",gunModelId.c_str());
            string gunNameStr = StringUtils::format("%s_name.png",gunModelId.c_str());
            Sprite * icon = Sprite::create(ImagePath(gunIconStr));
            icon->setPosition(iconBg->getContentSize().width * 0.75 - itemBg->getContentSize().width * 0.5, 0);
            addChild(icon);
            Sprite * iconName = Sprite::create(ImagePath(gunNameStr));
            iconName->setPosition(-itemBg->getContentSize().width * 0.25 + iconName->getContentSize().width * 1, itemBg->getContentSize().height * 0.18);
            addChild(iconName);
            
        }
            break;
        case 1:
        {
            itemBg = Sprite::create(ImagePath("shopItemBg1.png"));
            addChild(itemBg);
        }
            break;
        case 2:
        {
            itemBg = Sprite::create(ImagePath("shopItemBg1.png"));
            addChild(itemBg);
        }
            break;
        case 3:
        {
            itemBg = Sprite::create(ImagePath("shopItemBg1.png"));
            addChild(itemBg);
        }
            break;
        default:
            break;
    }
    
}
ShopItemScrollHeadler::~ShopItemScrollHeadler()
{
    
}