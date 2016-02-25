//
//  BuildingSpriteView.cpp
//  SwampAttack
//
//  Created by oceantech02 on 16/2/22.
//
//

#include "BuildingSpriteView.hpp"

#include "GameMapManager.h"
#include "GameFightScene.h"
#include "DefenseBuildingManager.h"
#include "GunManager.h"

BuildingSpriteView::BuildingSpriteView(DefenseBuilding * building):m_building(building)
{
    init();
    
    setSubject(m_building);

    m_iconScale = 0.5;
    int gunNum = GunManager::getInstance()->getTakeUpGunNum();
    int iconIndex = m_building->getShowIndex();
    m_greenBg = Sprite::create(ImagePath("fight_gun_greenBg.png"));
    m_blueBg = Sprite::create(ImagePath("fight_gun_blueBg.png"));
    Sprite * buildingIcon = Sprite::create(ImagePath(StringUtils::format("%s_icon.png",m_building->getModelId().c_str())));
    
    addChild(m_greenBg);
    addChild(m_blueBg);
    addChild(buildingIcon,5);
    
    m_greenBg->setScale(m_iconScale);
    m_blueBg->setScale(m_iconScale);
    buildingIcon->setScale(0.45);
    Vec2 iconPoint = _G_M_M->fightScene_gunIcon_Position;
    float iconWidth = m_greenBg->getContentSize().width;
    gunNum = gunNum > 1 ? gunNum : 0;
    Vec2 iconPointOff = iconPoint + Vec2((iconWidth + 10) * (gunNum + iconIndex), 0) * m_iconScale;
    m_greenBg->setPosition(iconPointOff);
    m_blueBg->setPosition(iconPointOff);
    buildingIcon->setPosition(iconPointOff);
    
    m_numProBar = new ProgressBar("fight_gun_greenBg.png");
    m_numProBar->autorelease();
    m_numProBar->setScale(m_iconScale);
    addChild(m_numProBar,6);
    m_numProBar->setBarChangeRate(Vec2(0, 1));
    m_numProBar->setBarUp();
    m_numProBar->setPosition(iconPointOff);
//    m_numProBar->updatePercent(60);
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(BuildingSpriteView::touchBegan, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(BuildingSpriteView::touchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, m_greenBg);
    
    updateData();
    _G_V->addChild(this,640);
}
BuildingSpriteView::~BuildingSpriteView()
{
    detachSubject();
    if(m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
bool BuildingSpriteView::touchBegan(Touch *touch, Event *event)
{
    Vec2 p = m_greenBg->convertToNodeSpace(touch->getLocation());
    Rect r = Rect(0, 0, m_greenBg->getContentSize().width,m_greenBg->getContentSize().height);
    if (r.containsPoint(p)) {
        return true;
    }
    return false;
}
void BuildingSpriteView::touchEnd(Touch *touch, Event *event)
{
    if (m_building->isCanHurt())
    {
        m_building->useBuildingJishu();
        m_building->setStateHurting();
    }
    
}
void BuildingSpriteView::updateData()
{
    int deadNum = m_building->getDeadNumber();
    int jishu = m_building->getBuildingJishu();
    float per = 100.0f - ((float)jishu/(float)deadNum) * 100;
    m_numProBar->updatePercent(per);
}