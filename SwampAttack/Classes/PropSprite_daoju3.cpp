//
//  PropSprite_daoju3.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/3.
//
//

#include "PropSprite_daoju3.h"
#include "GameMapManager.h"
#include "BaseUtil.h"


PropSprite_daoju3::PropSprite_daoju3(string propId):PropSprite(propId)
{
    
}
void PropSprite_daoju3::readyToHurt()
{
//    log("ready to hurt");
    if (m_prop->checkCanToHurt())
    {
        canToHurt();
    }
}
void PropSprite_daoju3::canToHurt()
{
    if (m_state == p_s_hurting)
    {
        return;
    }
    m_state = p_s_hurting;
    
    ActionInterval * a2 = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex("explosion", 14), NULL);
    ActionInterval * a1 = Sequence::create(DelayTime::create(0.08 * 5),
                                           CallFuncN::create(CC_CALLBACK_1(PropSprite_daoju3::hurtCall, this)), NULL);
    m_propTexiao->stopAllActions();
    m_propTexiao->removeAllChildrenWithCleanup(true);
    m_propTexiao->runAction(Sequence::create(
                                   Spawn::create(a1,a2, NULL),
                                   CallFuncN::create(CC_CALLBACK_1(PropSprite_daoju3::spriteCall2, this)),
                                   NULL) );
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("boom.mp3").c_str());
}

void PropSprite_daoju3::throwProp()
{
    if (m_state == p_s_throwing)
    {
        return;
    }
    m_state = p_s_throwing;
    
    
    //    propThrowCall(NULL);
    Vec2 startPoint = _G_M_M->m_BulletStartPoint;
    Vec2 tagetPoint = m_prop->getPropPoint();
    
    m_propTexiao = Sprite::create(ImagePath("daoju3.png"));
    m_propTexiao->setPosition(startPoint);
    addChild(m_propTexiao,6);
    
    float tatolTime = (tagetPoint.x - startPoint.x) * 0.001;
    
//    ActionInterval * a1 = Sequence::create(MoveTo::create(tatolTime, tagetPoint),NULL);
    float topPoint = (tagetPoint.x - startPoint.x) * 0.4 * 0.3;
    
    ccBezierConfig conf;
    conf.controlPoint_1 = Vec2(startPoint.x + (tagetPoint.x - startPoint.x) * 0.3, startPoint.y + topPoint);
    conf.controlPoint_2 = Vec2(startPoint.x + (tagetPoint.x - startPoint.x) * 0.6, startPoint.y + topPoint);
    conf.endPosition =tagetPoint;
    ActionInterval * a1 = BezierTo::create(tatolTime, conf);
    
//    ActionInterval * a2 = RepeatForever::create(Sequence::create(BaseUtil::makeAnimateWithNameAndIndex("daoju2", 8), NULL));
//    Sprite * s2 =Sprite::create();
//    m_propTexiao->addChild(s2);
//    s2->runAction(a2);
    
    m_propTexiao->runAction(Sequence::create(a1,CallFuncN::create(CC_CALLBACK_1(PropSprite_daoju3::propThrowCall, this)),NULL));
}
void PropSprite_daoju3::hurtCall(Node * psender)
{
    m_prop->setStateCanToHurt();
}
void PropSprite_daoju3::spriteCall2(Node * psender)
{
    m_prop->setStateDie();
    m_state = p_s_normal;
    Sprite * ss = (Sprite *)psender;
    ss->stopAllActions();
    ss->removeFromParentAndCleanup(true);
}