//
//  PropSprite_daoju1.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/3.
//
//

#include "PropSprite_daoju1.h"
#include "GameMapManager.h"
#include "BaseUtil.h"

PropSprite_daoju1::PropSprite_daoju1(Prop * pp):PropSprite(pp)
{
    
}
void PropSprite_daoju1::throwProp()
{
    if (m_state == p_s_throwing)
    {
        return;
    }
    m_state = p_s_throwing;
    
    log("throw prop");
    
//    propThrowCall(NULL);
    Vec2 startPoint = _G_M_M->m_BulletStartPoint;
    Vec2 tagetPoint = m_prop->getPropPoint();
    
    m_propTexiao = Sprite::create();
    m_propTexiao->setPosition(startPoint);
    addChild(m_propTexiao,6);
    
    float tatolTime = (tagetPoint.x - startPoint.x) * 0.001;
    
    ActionInterval * a1 = Sequence::create(MoveTo::create(tatolTime, tagetPoint),NULL);
    
    ActionInterval * a2 = RepeatForever::create(Sequence::create(BaseUtil::makeAnimateWithNameAndIndex("daoju1", 8), NULL));
    Sprite * s2 =Sprite::create();
    m_propTexiao->addChild(s2);
    s2->runAction(a2);
    
    m_propTexiao->runAction(Sequence::create(a1,CallFuncN::create(CC_CALLBACK_1(PropSprite_daoju1::spriteCall, this)),NULL));
    
}
void PropSprite_daoju1::spriteCall(Node * psender)
{
    ActionInterval * a2 = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex("explosion", 14), NULL);
    ActionInterval * a1 = Sequence::create(DelayTime::create(0.08 * 5),
                                   CallFuncN::create(CC_CALLBACK_1(PropSprite_daoju1::propThrowCall, this)), NULL);
    Sprite * ss = (Sprite *)psender;
    ss->stopAllActions();
    ss->removeAllChildrenWithCleanup(true);
    ss->runAction(Sequence::create(
                                   Spawn::create(a1,a2, NULL),
                                   CallFuncN::create(CC_CALLBACK_1(PropSprite_daoju1::spriteCall2, this)),
                                   NULL) );
}
void PropSprite_daoju1::spriteCall2(Node * psender)
{
    Sprite * ss = (Sprite *)psender;
    ss->stopAllActions();
    ss->removeFromParentAndCleanup(true);
}