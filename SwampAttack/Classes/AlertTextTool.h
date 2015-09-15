//
//  AlertTextTool.h
//  SwampAttack
//
//  Created by oceantech02 on 15/9/9.
//
//

#ifndef __SwampAttack__AlertTextTool__
#define __SwampAttack__AlertTextTool__

#include "BaseCode.h"

#define AlertText(text ,size) AlertTextTool::getInstance()->alertText(text ,size)

using namespace std;

struct AlertData
{
//    Node *  node;
    string  text;
    int     size;
};

class AlertTextTool {
private:
    queue<AlertData>    m_alertData;
    queue<Label *>      m_showLabels;
    
    
    AlertTextTool();
    ~AlertTextTool();
    
    void showNext();
    void removeText(Node * pSender);
public:
    static AlertTextTool * getInstance();
    void alertText(string text, int size = 20);
    
};

#endif /* defined(__SwampAttack__AlertTextTool__) */
