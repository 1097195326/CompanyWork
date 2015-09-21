//
//  BulletSprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "BulletSprite.h"
#include "GameFightScene.h"
#include "BaseUtil.h"


BulletSprite::BulletSprite()
{
    init();
    
    
    
    scheduleUpdate();
    _G_V->addChild(this,2);
}
BulletSprite::~BulletSprite()
{
    
}
void BulletSprite::setModel(Bullet *bullet)
{
    m_model = bullet;
    std::string dandao = m_model->getModelId();
    
    
    BulletInfoData infoData = m_model->getDandaoInfo();
    if (infoData.frames == 1)
    {
        initWithFile(ImagePath(StringUtils::format("%s.png",infoData.name.c_str())));
    }else
    {
        if (m_model->getFlyActionType() == 3)
        {
            Action * ac = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(infoData.name, infoData.frames),NULL);
            runAction(ac);
        }else
        {
            Action * ac = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex(infoData.name, infoData.frames));
            runAction(ac);
        }
    }
    
}
void BulletSprite::update(float data)
{
    if (m_model->isMoving()) {
        setPosition(m_model->getPosition());
    }else if (m_model->isArrive())
    {
        m_model->arriveCall();
        if (m_model->isHaveExplode())
        {
            BulletInfoData infoData = m_model->getBaozhaTexiaoInfo();
            _G_V->addBulletTexiao(m_model->getPosition(), infoData.name, infoData.frames);
        }
        
    }else if (m_model->isDie())
    {
        m_model->setCanDelete();
        unscheduleUpdate();
        stopAllActions();
        removeAllChildrenWithCleanup(true);
        removeFromParentAndCleanup(true);
        return;
    }
}