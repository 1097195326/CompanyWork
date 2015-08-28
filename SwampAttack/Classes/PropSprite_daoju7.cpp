//
//  PropSprite_daoju7.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/8/5.
//
//

#include "PropSprite_daoju7.h"
#include "GameMapManager.h"
#include "BaseUtil.h"


PropSprite_daoju7::PropSprite_daoju7(string propId):PropSprite(propId)
{
    
}
void PropSprite_daoju7::throwProp()
{
    if (m_state == p_s_throwing)
    {
        return;
    }
    m_state = p_s_throwing;
    
    
    //    propThrowCall(NULL);
    Vec2 startPoint = _G_M_M->m_BulletStartPoint;
    Vec2 tagetPoint = m_prop->getPropPoint();
    
    m_propTexiao = Sprite::create();
    m_propTexiao->setPosition(startPoint);
    addChild(m_propTexiao,6);
    
    string modelId = m_prop->getModelId();
    
    float tatolTime = (tagetPoint.x - startPoint.x) * 0.001;
    
    //    ActionInterval * a1 = Sequence::create(MoveTo::create(tatolTime, tagetPoint),NULL);
    float topPoint = (tagetPoint.x - startPoint.x) * 0.4 * 0.3;
    
    ccBezierConfig conf;
    conf.controlPoint_1 = Vec2(startPoint.x + (tagetPoint.x - startPoint.x) * 0.3, startPoint.y + topPoint);
    conf.controlPoint_2 = Vec2(startPoint.x + (tagetPoint.x - startPoint.x) * 0.6, startPoint.y + topPoint);
    conf.endPosition =tagetPoint;
    ActionInterval * a1 = BezierTo::create(tatolTime, conf);
    
    ActionInterval * a2 = RepeatForever::create(Sequence::create(BaseUtil::makeAnimateWithNameAndIndex(modelId, 8), NULL));
    Sprite * s2 =Sprite::create();
    m_propTexiao->addChild(s2);
    s2->runAction(a2);
    
    m_propTexiao->runAction(Sequence::create(a1,CallFuncN::create(CC_CALLBACK_1(PropSprite_daoju7::spriteCall, this)),NULL));
}
void PropSprite_daoju7::spriteCall(Node * psender)
{
    ActionInterval * a2 = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex("lighting", 6), NULL);
    ActionInterval * a1 = Sequence::create(DelayTime::create(0.08 * 1),
                                           CallFuncN::create(CC_CALLBACK_1(PropSprite_daoju7::propThrowCall, this)), NULL);
    
//    ActionInterval * a3 = BaseUtil::makeAnimateWithNameAndIndex("lighting", 6);
    
    Sprite * ss = (Sprite *)psender;
    ss->stopAllActions();
    ss->removeAllChildrenWithCleanup(true);
    ss->runAction(Sequence::create(
                                   Spawn::create(a1,a2, NULL),
                                   CallFuncN::create(CC_CALLBACK_1(PropSprite_daoju7::spriteCall2, this)),
                                   NULL) );
    string modelId = m_prop->getModelId();
    SimpleAudioEngine::getInstance()->playEffect(MusicPath(modelId + ".mp3").c_str());
}
void PropSprite_daoju7::spriteCall2(Node * psender)
{
    m_prop->setStateDie();
    Sprite * ss = (Sprite *)psender;
    ss->stopAllActions();
    ss->removeFromParentAndCleanup(true);
}