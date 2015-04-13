//
//  EnemySprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "EnemySprite.h"
#include "BaseUtil.h"


EnemySprite::EnemySprite(string name)
{
    Action * walkAction = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_walk", 14));
    walkAction->retain();
    Action * hurtAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(name + "_hurt", 10),
                                           CallFunc::create(CC_CALLBACK_0(EnemySprite::hurtCall, this)),
                                           NULL);
    hurtAction->retain();
    Action * attackAction = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(name + "attack", 12),
                                             CallFunc::create(CC_CALLBACK_0(EnemySprite::attackCall, this)),
                                             NULL);
    attackAction->retain();
    
    m_map["walkAction"] = walkAction;
    m_map["hurtAction"] = hurtAction;
    m_map["attackAction"] = attackAction;
    
    scheduleUpdate();
}
EnemySprite::~EnemySprite()
{
    std::map<std::string, Action * >::iterator itr;
    for (itr = m_map.begin(); itr != m_map.end(); itr++) {
        Action * ac = itr->second;
        ac->release();
    }
    m_map.clear();
    
}
void EnemySprite::update(float data)
{
    
}
void EnemySprite::setMode(Enemy *model)
{
    m_model = model;
}
void EnemySprite::move()
{
    runAction(m_map["walkAction"]);
}
void EnemySprite::hurt()
{
    runAction(m_map["hurtAction"]);
}
void EnemySprite::attack()
{
    runAction(m_map["attackAction"]);
}
void EnemySprite::hurtCall()
{
    
}
void EnemySprite::attackCall()
{
    
}