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
void AlertTextTool::alertText(Node * node, string text,int size)
{
    AlertData data = {node, text, size};
    m_alertData.push(data);
    
//    while (m_alertData.size() > 0)
//    {
//        AlertData data = m_alertData.front();
//        
//        
//    }
    
    
}
void AlertTextTool::showNext()
{
    
}
void AlertTextTool::removeText(cocos2d::Node *pSender)
{
    pSender->stopAllActions();
    pSender->removeFromParentAndCleanup(true);
}