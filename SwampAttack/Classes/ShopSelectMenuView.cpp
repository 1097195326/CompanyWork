//
//  ShopSelectMeumView.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#include "ShopSelectMenuView.h"
#include "GameSprite.h"

ShopSelectMenuView::ShopSelectMenuView(int num):SelectMenuView(num)
{
    
}
ShopSelectMenuView::~ShopSelectMenuView()
{
//    if (m_listener) {
//        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
//    }
}

void ShopSelectMenuView::setNormalSprite(std::string name)
{
//    m_listener = EventListenerTouchOneByOne::create();
//    m_listener->setSwallowTouches(true);
//    m_listener->onTouchBegan = CC_CALLBACK_2(ShopSelectMenuView::touchBegan, this);
//    m_listener->onTouchEnded = CC_CALLBACK_2(ShopSelectMenuView::touchEnd, this);
    
    for (int i = 0; i < m_num; ++i)
    {
        GameSprite * s = new GameSprite(ImagePath("shopItemNormal.png"));
//        Sprite * s = Sprite::create(ImagePath("shopItemNormal.png"));
        s->autorelease();
        s->setCanSwallowTouches(true);
        s->setPosition(i * 205 - 310, 0);
        s->setTag(i);
//        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener->clone(), s);
        s->m_touchMeCall = CC_CALLBACK_2(ShopSelectMenuView::touchEnd, this);
        addChild(s,1);
        Size size = s->getContentSize();
        Sprite * s_i = Sprite::create(ImagePath(StringUtils::format("shopItemIcon%d.png",i+1)));
        s_i->setPosition(size.width * 0.5,size.height * 0.5);
        s->addChild(s_i);
        
        m_normalSprites[i] = s;
    }
}
void ShopSelectMenuView::setSelectSprite(std::string name)
{
    for (int i = 0; i < m_num; ++i)
    {
        Sprite * s = Sprite::create(ImagePath(StringUtils::format("%s%d.png",name.c_str(),i+1)));
        addChild(s,2);
        Size size = s->getContentSize();
        Sprite * s_i = Sprite::create(ImagePath(StringUtils::format("shopItemIcon%d.png",i+1)));
        s_i->setPosition(size.width * 0.145 + size.width * 0.238 * i,size.height * 0.58);
        s->addChild(s_i);
        
        m_selectSprites[i] = s;
    }
}
void ShopSelectMenuView::setIconSprite(std::string name)
{
    for (int i = 0; i < m_num; ++i)
    {
        Sprite * s = Sprite::create(ImagePath(StringUtils::format("%s%d.png",name.c_str(),i+1)));
        s->setPosition(i * 205 - 310, 20);
        addChild(s,3);
    }
}
void ShopSelectMenuView::checkIndex()
{
    int selectIndex = m_controller->getSelectIndex();
    for (int i = 0; i < m_num; ++i)
    {
        if (i == selectIndex)
        {
            m_normalSprites[i]->setVisible(false);
            m_selectSprites[i]->setVisible(true);
        }else
        {
            m_normalSprites[i]->setVisible(true);
            m_selectSprites[i]->setVisible(false);
        }
    }
    notify();
}
//bool ShopSelectMenuView::touchBegan(Touch *touch, Event *event)
//{
//    //    log("touch");
//    Sprite * s = (Sprite *) event->getCurrentTarget();
//    Vec2 p = s->convertToNodeSpace(touch->getLocation());
//    Size size = s->getContentSize();
//    Rect r = Rect(0, 0, size.width, size.height);
//    if (r.containsPoint(p)) {
////        log("sprite tag :%d",s->getTag());
//        return true;
//    }
//    return false;
//}
void ShopSelectMenuView::touchEnd(Touch *touch, Event *event)
{
    Sprite * s = (Sprite *) event->getCurrentTarget();
    int tag = s->getTag();
    m_controller->selectMenu(tag);
    checkIndex();
}
void ShopSelectMenuView::setSelectIndex(int index)
{
    m_controller->selectMenu(index);
    checkIndex();
}