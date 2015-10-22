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
    
    attackWaitTime = m_model->getAttackWaitTime();
//    Sprite * s = Sprite::create("CloseSelected.png");
//    s->setPosition(Vec2(0, h * 0.5));
//    addChild(s);
    
    if (m_model->getActionType() != 2 && !m_model->isBoss())
    {
        diyingSprite = Sprite::create(ImagePath("enemy_yinying.png"));
        diyingSprite->setOpacity(170);
        diyingSprite->setPosition(w * 0.15, h * 0.05);
        diyingSprite->setScale(0.8);
        addChild(diyingSprite);
    }
    
    healthBar = new ProgressBar("xuenei.png","xuewai.png");
    addChild(healthBar,1);
    healthBar->setBarLeft();
    healthBar->setPosition(Vec2(0, h * 0.9));
    healthBar->setVisible(false);
    
    guaiwuSprite = Sprite::create();
    guaiwuSprite->setPosition(Vec2(0, h * 0.5));
    addChild(guaiwuSprite);
//    guaiwuSprite->setScale(1.2);
    
    buffSprite = Sprite::create();
    buffSprite->setPosition(Vec2(0, h * 0.5));
    addChild(buffSprite,1);
    
    texiaoSprite = Sprite::create();
    texiaoSprite->setPosition(Vec2(0, h * 0.5));
    addChild(texiaoSprite,2);
    texiaoAction = Sequence::create(Spawn::create(
                                                  BaseUtil::makeAnimateWithNameAndIndex("blood", 7),
                                                  BaseUtil::makeAnimateWithNameAndIndex("hit", 4),
                                                  NULL),
                                    CallFunc::create(CC_CALLBACK_0(EnemySprite::texiaoCall, this)),
                                    NULL);
    ;
    texiaoAction->retain();
    if (!_G_V) {
        log("game fight layer is null");
    }
    _G_V->addChild(this,640 - m_model->getPosition().y);
    setPosition(m_model->getPosition());
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
void EnemySprite::attack(float data)
{}
void EnemySprite::die()
{}
void EnemySprite::hurt()
{}
void EnemySprite::dianji()
{}
void EnemySprite::texiaoCall()
{
    texiaoSprite->setVisible(false);
}
void EnemySprite::attackCall()
{
    actionStatus = normal;
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("enemy_attack.mp3").c_str());
    m_model->attackCall();
}
void EnemySprite::dieCall()
{
//    log("----- die");
    m_model->dieingCall();
}
void EnemySprite::hurtCall()
{
    actionStatus = normal;
    m_model->hurtCall();
}
void EnemySprite::dianjiCall()
{
    actionStatus = normal;
    m_model->dianjiCall();
}