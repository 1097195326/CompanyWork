//
//  AlertTextTool.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/9/9.
//
//

#include "AlertTextTool.h"


AlertTextTool::AlertTextTool()
{
    
}
AlertTextTool::~AlertTextTool()
{
    
}
AlertTextTool * AlertTextTool::getInstance()
{
    static AlertTextTool alertTextTool;
    return &alertTextTool;
}
void AlertTextTool::alertText(string text,int size)
{
    AlertData data = {text, size};
    
    if (m_showLabels.size() <5)
    {
        m_alertData.push(data);
    }
    showNext();
}
void AlertTextTool::showNext()
{
    int showNum = (int)m_showLabels.size();
    if (m_alertData.size() > 0 && showNum <= 5)
    {
        float l_h = 40;
        float l_p = m_visibleOrigin.y + m_visibleSize.height * 0.7;
        
        AlertData data = m_alertData.front();
        
        Label * showLabel = Label::createWithTTF(data.text,
                                                 FontPath,
                                                 data.size);
        showLabel->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                               l_p - l_h * showNum);
//        showLabel->setLineHeight(35);
//        showLabel->setDimensions(400,100);
        
//        data.node->addChild(showLabel,1000);
        Scene * runScene = Director::getInstance()->getRunningScene();
        runScene->addChild(showLabel,1000);
        
        m_showLabels.push(showLabel);
        m_alertData.pop();
        
        showLabel->runAction(Sequence::create(DelayTime::create(0.5),
                                              CallFunc::create(CC_CALLBACK_0(AlertTextTool::showNext, this)),
                                              DelayTime::create(0.5),
                                              Spawn::create(MoveBy::create(0.3, Vec2(0, 30)),
                                                            FadeOut::create(0.3),
                                                            NULL),
                                              CallFuncN::create(CC_CALLBACK_1(AlertTextTool::removeText, this)),
                                              NULL));
    }
    
}
void AlertTextTool::removeText(cocos2d::Node *pSender)
{
    pSender->stopAllActions();
    pSender->removeFromParentAndCleanup(true);
    m_showLabels.pop();
}