//
//  PropSprite_daoju6.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/5.
//
//

#include "PropSprite_daoju6.h"
#include "GameMapManager.h"
#include "BaseUtil.h"
#include "GameFightScene.h"

PropSprite_daoju6::PropSprite_daoju6(string propId):PropSprite(propId)
{
    
}
void PropSprite_daoju6::throwProp()
{
    if (m_state == p_s_throwing)
    {
        return;
    }
    m_state = p_s_throwing;
    
    
    Vec2 tagetPoint = m_prop->getPropPoint() + Vec2(0, 50);
    
    m_propTexiao = Sprite::create(ImagePath("daoju6.png"));
    m_propTexiao->setPosition(Vec2(tagetPoint.x,1000));
    m_propTexiao->setScale(1.5);
    addChild(m_propTexiao,6);
    
    float tatolTime = (800 - tagetPoint.y) * 0.001;
    
    ActionInterval * a1 = Sequence::create(EaseBounceIn::create(MoveTo::create(tatolTime, tagetPoint)),NULL);
    
//    ActionInterval * a2 = RepeatForever::create(Sequence::create(BaseUtil::makeAnimateWithNameAndIndex("daoju6", 10), NULL));
//    Sprite * s2 =Sprite::create();
//    m_propTexiao->addChild(s2);
//    s2->runAction(a2);
    
    m_propTexiao->runAction(Sequence::create(a1,CallFuncN::create(CC_CALLBACK_1(PropSprite_daoju6::spriteCall, this)),NULL));
}
void PropSprite_daoju6::spriteCall(Node * psender)
{
    ActionInterval * a2 = Sequence::create(BaseUtil::makeAnimateWithNameAndIndex("nulear", 38), NULL);
//        ActionInterval * a1 = Sequence::create(DelayTime::create(0.08 * 16),
//                                               CallFuncN::create(CC_CALLBACK_1(PropSprite_daoju6::propThrowCall, this)),
//                                               NULL);
    propThrowCall(NULL);
    
    Sprite * ss = (Sprite *)psender;
    ss->stopAllActions();
    ss->removeAllChildrenWithCleanup(true);
    _G_V->shanBai();
    _G_V->zhenPingUpDown();
    ss->runAction(Sequence::create(a2,
                                   CallFuncN::create(CC_CALLBACK_1(PropSprite_daoju6::spriteCall2, this)),
                                   NULL) );
    
    string modelId = m_prop->getModelId();
    SimpleAudioEngine::getInstance()->playEffect(MusicPath(modelId + ".mp3").c_str());
}
void PropSprite_daoju6::spriteCall2(Node * psender)
{
    log("dao ju 6 call2");
    m_prop->setStateDie();
    Sprite * ss = (Sprite *)psender;
    ss->stopAllActions();
    ss->removeFromParentAndCleanup(true);
}