//
//  HouseSprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/29.
//
//

#include "HouseSprite.h"
#include "GameMapManager.h"
#include "GameFightScene.h"


HouseSprite::HouseSprite()
{
    init();
    
    Sprite * houseSprite = Sprite::create(ImagePath("house.png"));
    addChild(houseSprite);
    houseSprite->setPosition(_G_M_M->fightScene_HouseSprite_Position);
    
    m_healthBar = new ProgressBar("fight_house_bar.png","fight_house_barbg.png");
    addChild(m_healthBar);
    m_healthBar->setBarRight();
    m_healthBar->setPosition(_G_M_M->fightScene_HouseBar_Position);
    log("house bar :%f",_G_M_M->fightScene_HouseBar_Position.y);
    _G_V->addChild(this,1);
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
    initView();
}
void HouseSprite::initView()
{
    
    
}