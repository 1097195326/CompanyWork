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
    EventListenerTouchOneByOne * m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(ShopSelectMenuView::touchBegan, this);
    m_listener->onTouchMoved = CC_CALLBACK_2(ShopSelectMenuView::touchMoved,this);
    m_listener->onTouchEnded = CC_CALLBACK_2(ShopSelectMenuView::touchEnd, this);
    
    for (int i = 0; i < m_num; ++i)
    {
        Sprite * s = Sprite::create(ImagePath("shopItemNormal.png"));
        s->setPosition(i * 205 - 310, 30);
        s->setTag(i);
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener->clone(), s);
        addChild(s,1);
        m_normalSprites[i] = s;
    }
}
void ShopSelectMenuView::setSelectSprite(std::string name)
{
    for (int i = 0; i < m_num; ++i)
    {
        Sprite * s = Sprite::create(ImagePath(StringUtils::format("%s%d.png",name.c_str(),i+1)));
        addChild(s,2);
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
bool ShopSelectMenuView::touchBegan(Touch *touch, Event *event)
{
    //    log("touch");
    Sprite * s = (Sprite *) event->getCurrentTarget();
    Vec2 p = s->convertToNodeSpace(touch->getLocation());
    Size size = s->getContentSize();
    Rect r = Rect(0, 0, size.width, size.height);
    if (r.containsPoint(p)) {
//        log("sprite tag :%d",s->getTag());
        return true;
    }
    return false;
}
void ShopSelectMenuView::touchEnd(Touch *touch, Event *event)
{
    Sprite * s = (Sprite *) event->getCurrentTarget();
    int tag = s->getTag();
    m_controller->selectMenu(tag);
    checkIndex();
}