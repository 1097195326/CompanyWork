//
//  PropSpriteView.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/4.
//
//

#include "PropSpriteView.h"
#include "GameMapManager.h"
#include "GameFightScene.h"
#include "PropManager.h"

#include "GameUser.h"
#include "DropManager.h"
#include "BaseUtil.h"

#include "PropSprite_daoju1.h"
#include "PropSprite_daoju2.h"
#include "PropSprite_daoju3.h"
#include "PropSprite_daoju5.h"
#include "PropSprite_daoju6.h"
#include "PropSprite_daoju7.h"
#include "PropSprite_daoju8.h"
#include "PropSprite_daoju9.h"

PropSpriteView::PropSpriteView(Prop * prop):
m_prop(prop),
m_moveJuli(0.0f)
{
    init();
    m_propIcon = NULL;
    
    m_iconScale = 0.48;
    int iconIndex = PropManager::getInstance()->getTakeUpPropIndexByName(m_prop->getId());
//    int iconIndex = m_prop->getTakeUpIndex();
    m_blueBg = Sprite::create(ImagePath("fight_gun_blueBg.png"));
    Sprite * propIcon = Sprite::create(ImagePath(StringUtils::format("%s_icon.png",m_prop->getModelId().c_str())));
    m_numLabel = Label::createWithTTF(StringUtils::format("%d",m_prop->getNum()),
                                      "fonts/Arial Black.ttf",
                                      20);
    m_numLabel->enableOutline(Color4B(0, 0, 0, 255),2);
    addChild(m_blueBg);
    addChild(propIcon,5);
    addChild(m_numLabel,5);
    
    m_blueBg->setScale(m_iconScale);
    propIcon->setScale(0.5);
    
    Vec2 iconPoint = _G_M_M->fightScene_PropIcon_Position;
    float iconWidth = m_blueBg->getContentSize().width;
    m_blueBg->setPosition(iconPoint - Vec2((iconWidth + 0) * (iconIndex - 1), 0) * m_iconScale);
    propIcon->setPosition(iconPoint - Vec2((iconWidth + 0) * (iconIndex - 1), 0) * m_iconScale);
    m_numLabel->setPosition(iconPoint - Vec2((iconWidth + 0) * (iconIndex - 1), 0) * m_iconScale + Vec2(20, -20));
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(PropSpriteView::touchBegan, this);
    m_listener->onTouchMoved = CC_CALLBACK_2(PropSpriteView::touchMove, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(PropSpriteView::touchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, m_blueBg);
    
    if (!_G_U->isHaveXinshouYindao()) {
//        schedule(CC_SCHEDULE_SELECTOR(PropSpriteView::checkXinshou), 0.5, true, 0);
        schedule(CC_SCHEDULE_SELECTOR(PropSpriteView::checkXinshou), 0.5);
    }
    
    _G_V->addChild(this,640);
}
PropSpriteView::~PropSpriteView()
{
    if(m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
void PropSpriteView::checkXinshou(float data)
{
    if (_G_U->isHaveXinshouYindao())
    {
        unschedule(CC_SCHEDULE_SELECTOR(PropSpriteView::checkXinshou));
    }else
    {
        if (DropManager::getInstance()->getDropNum() == 0)
        {
            unschedule(CC_SCHEDULE_SELECTOR(PropSpriteView::checkXinshou));
            Action * dianJiAc = RepeatForever::create(Sequence::create(BaseUtil::makeAnimateWithNameAndIndex("shou", 6),
                                                                       EaseSineIn::create(MoveBy::create(0.3, Vec2(-50, -80))),
                                                                       DelayTime::create(0.6),
                                                                       MoveBy::create(0.1, Vec2(50, 80)),
                                                                       NULL));
            m_shou = Sprite::create();
            addChild(m_shou,6);
            
            int iconIndex = PropManager::getInstance()->getTakeUpPropIndexByName(m_prop->getId());
//            int iconIndex = m_prop->getTakeUpIndex();
            Vec2 iconPoint = _G_M_M->fightScene_PropIcon_Position;
            float iconWidth = m_blueBg->getContentSize().width;
            m_shou->setPosition(iconPoint - Vec2((iconWidth + 0) * (iconIndex - 1), 0) * m_iconScale + Vec2(10, -30));
            m_shou->setScale(0.5);
            m_shou->runAction(dianJiAc);
            
        }
    }
}
Vec2 PropSpriteView::getViewPosition()
{
    return m_blueBg->getPosition();
}
bool PropSpriteView::touchBegan(Touch *touch, Event *event)
{
    Vec2 p = m_blueBg->convertToNodeSpace(touch->getLocation());
    Rect r = Rect(0, 0, m_blueBg->getContentSize().width ,m_blueBg->getContentSize().height);
    if (r.containsPoint(p))
    {
        if (m_prop->getNum() <= 0)
        {
            return false;
        }
        if (m_prop->getModelId() == "daoju1")
        {
            m_propIcon = new PropSprite_daoju1(m_prop->getId());
        }else if (m_prop->getModelId() == "daoju2")
        {
            m_propIcon = new PropSprite_daoju2(m_prop->getId());
        }else if (m_prop->getModelId() == "daoju3")
        {
            m_propIcon = new PropSprite_daoju3(m_prop->getId());
        }else if (m_prop->getModelId() == "daoju5")
        {
            m_propIcon = new PropSprite_daoju5(m_prop->getId());
        }else if (m_prop->getModelId() == "daoju6")
        {
            m_propIcon = new PropSprite_daoju6(m_prop->getId());
        }else if (m_prop->getModelId() == "daoju7")
        {
            m_propIcon = new PropSprite_daoju7(m_prop->getId());
        }else if (m_prop->getModelId() == "daoju8")
        {
            m_propIcon = new PropSprite_daoju8(m_prop->getId());
        }else if (m_prop->getModelId() == "daoju9")
        {
            m_propIcon = new PropSprite_daoju9(m_prop->getId());
        }else
        {
            m_propIcon = new PropSprite(m_prop->getId());
        }
        m_propIcon->autorelease();
        _G_V->addChild(m_propIcon,640);
         m_propIcon->moveIng(m_blueBg->getPosition());
        return true;
    }
    return false;
}
void PropSpriteView::touchMove(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Vec2 touchPoint = touch->getLocation();
    m_propIcon ->moveIng(touchPoint);
}
void PropSpriteView::touchEnd(Touch *touch, Event *event)
{
    Vec2 p = m_blueBg->convertToNodeSpace(touch->getLocation());
    Rect r = Rect(0, 0, m_blueBg->getContentSize().width ,m_blueBg->getContentSize().height);
    if (r.containsPoint(p) || touch->getLocation().x <= _G_M_M->m_BulletStartPoint.x)
    {
        m_propIcon->removeFromParentAndCleanup(true);
        m_propIcon = NULL;
    }else
    {
        if (!_G_U->isHaveXinshouYindao()) {
            m_shou->stopAllActions();
            m_shou->removeAllChildrenWithCleanup(true);
            m_shou->removeFromParentAndCleanup(true);
            _G_U->setIsHaveXinshouYindao();
            _G_V->resumeGame();
        }
        
        m_prop->useProp();
        m_propIcon->moveEnd();
        m_propIcon = NULL;
        
    }
    
}
void PropSpriteView::updateData()
{
    
    m_numLabel->setString(StringUtils::format("%d",m_prop->getNum()));
    
}