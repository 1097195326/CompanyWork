//
//  EnemySprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "EnemySprite.h"

#include "GameFightScene.h"



EnemySprite::EnemySprite(Enemy * model):m_model(model),isHaveArmor(false)
{
    init();
    setAnchorPoint(Vec2(0.5,0));
    
    int w = m_model->getWidth();
    int h = m_model->getHeight();
    
    healthBar = new ProgressBar("xuenei.png","xuewai.png");
    addChild(healthBar,1);
    healthBar->setBarLeft();
    healthBar->setPosition(Vec2(w * 0.5, h * 0.9));
    healthBar->setVisible(false);
    
    texiaoSprite = Sprite::create();
    texiaoSprite->setPosition(Vec2(w * 0.5, h * 0.5));
    addChild(texiaoSprite,2);
    texiaoAction = Sequence::create(Spawn::create(
                                                  BaseUtil::makeAnimateWithNameAndIndex("blood", 7),
                                                  BaseUtil::makeAnimateWithNameAndIndex("hit", 4),
                                                  NULL),
                                    CallFunc::create(CC_CALLBACK_0(EnemySprite::texiaoCall, this)),
                                    NULL);
    ;
    texiaoAction->retain();
    _G_V->addChild(this,640 - m_model->getPosition().y);
}
EnemySprite::~EnemySprite()
{
    std::map<std::string, Action * >::iterator itr;
    for (itr = m_map.begin(); itr != m_map.end(); itr++) {
        Action * ac = itr->second;
        ac->release();
    }
    m_map.clear();
    
    removeAllChildrenWithCleanup(true);
    delete healthBar;
    texiaoAction->release();
}
void EnemySprite::move()
{}
void EnemySprite::attack()
{}
void EnemySprite::die()
{}
void EnemySprite::hurt()
{}
void EnemySprite::texiaoCall()
{
    texiaoSprite->setVisible(false);
}
void EnemySprite::attackCall()
{
    m_model->attackCall();
}
void EnemySprite::dieCall()
{
    m_model->dieingCall();
}
void EnemySprite::hurtCall()
{
    actionStatus = normal;
    m_model->hurtCall();
}