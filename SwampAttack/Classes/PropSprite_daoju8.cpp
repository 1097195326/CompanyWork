//
//  PropSprite_daoju8.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/8/5.
//
//

#include "PropSprite_daoju8.h"
#include "GameMapManager.h"
#include "BaseUtil.h"


PropSprite_daoju8::PropSprite_daoju8(string propId):PropSprite(propId)
{
    
}
void PropSprite_daoju8::throwProp()
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
    
    m_propTexiao->runAction(Sequence::create(a1,CallFuncN::create(CC_CALLBACK_1(PropSprite_daoju8::spriteCall, this)),NULL));
}
void PropSprite_daoju8::spriteCall(Node * psender)
{
    ActionInterval * a2 = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex("daoju8_broken", 5), NULL);
    ActionInterval * a1 = Sequence::create(DelayTime::create(0.08 * 1),
                                           CallFuncN::create(CC_CALLBACK_1(PropSprite_daoju8::spriteCall2, this)), NULL);
    Sprite * ss = (Sprite *)psender;
    ss->stopAllActions();
    ss->removeAllChildrenWithCleanup(true);
    ss->runAction(Sequence::create(
                                   Spawn::create(a1,a2, NULL),
                                   CallFuncN::create(CC_CALLBACK_1(PropSprite_daoju8::spriteCall3, this)),
                                   NULL) );
    string modelId = m_prop->getModelId();
    SimpleAudioEngine::getInstance()->playEffect(MusicPath(modelId + ".mp3").c_str());
}
void PropSprite_daoju8::spriteCall2(Node * psender)
{
    Sprite * ss = (Sprite *)psender;
    
    Sprite * s = Sprite::create(ImagePath("daoju8_youzi.png"));
    s->setScale(1.5);
    s->setPosition(ss->getPosition());
    addChild(s);
    runAction(FadeIn::create(0.3));
    
    
}
void PropSprite_daoju8::spriteCall3(cocos2d::Node *psender)
{
    Sprite * ss = (Sprite *)psender;
    ss->stopAllActions();
    ss->removeFromParentAndCleanup(true);
    propThrowCall(NULL);
}