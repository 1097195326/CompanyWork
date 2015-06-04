//
//  BuffSprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/4.
//
//

#include "BuffSprite.h"
#include "BaseUtil.h"


BuffSprite::BuffSprite(GameBuff * buff):
m_buff(buff)
{
    init();
    
    string buffModelId = m_buff->getModelId();
    
    Action * action = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex(buffModelId, m_buff->getFrames()));
    runAction(action);
    
    scheduleUpdate();
}

void BuffSprite::update(float data)
{
    if (m_buff->isDie())
    {
        stopAllActions();
        m_buff->removeFromModel();
        m_buff->setStateCanDelete();
        removeFromParentAndCleanup(true);
    }
}