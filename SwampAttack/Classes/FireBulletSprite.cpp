//
//  FireBulletSprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/7/29.
//
//

#include "FireBulletSprite.h"
#include "GameFightScene.h"
#include "BaseUtil.h"


FireBulletSprite::FireBulletSprite()
{
    init();
    
    
    
    scheduleUpdate();
    _G_V->addChild(this,2);
}
FireBulletSprite::~FireBulletSprite()
{
    
}
void FireBulletSprite::setModel(Bullet *bullet)
{
    m_model = bullet;
    std::string dandao = m_model->getModelId();
    
    
    BulletInfoData infoData = m_model->getDandaoInfo();
    if (infoData.frames == 1)
    {
        initWithFile(ImagePath(StringUtils::format("%s.png",infoData.name.c_str())));
    }else
    {
        Action * ac = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex(infoData.name, infoData.frames));
        runAction(ac);
    }
    setScale(0);
    
}
void FireBulletSprite::update(float data)
{
    if (m_model->isMoving()) {
        float s_x = m_model->getPosition().x - m_model->getStartPosition().x;
        setScale(s_x/450.0f);
        setPosition(m_model->getPosition().x / 2, m_model->getPosition().y);
        
    }else if (m_model->isArrive())
    {
        m_model->arriveCall();
        
    }else if (m_model->isDie())
    {
        m_model->setCanDelete();
        unscheduleUpdate();
        stopAllActions();
        removeFromParentAndCleanup(true);
        return;
    }
}