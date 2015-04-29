//
//  HouseSprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/29.
//
//

#include "HouseSprite.h"

HouseSprite::HouseSprite()
{
    init();
    
    m_healthBar = new ProgressBar("xuenei.png","xuewai.png");
    addChild(m_healthBar);
    m_healthBar->setBarRight();
    scheduleUpdate();
}
HouseSprite::~HouseSprite()
{
    delete m_healthBar;
}
void HouseSprite::update(float data)
{
//    log("----");
    m_healthBar->updatePercent(m_houseModel->getHealthPercent());
}
void HouseSprite::setModel(House * house)
{
    m_houseModel = house;
}