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

#define AlertText(node, text ,size) AlertTextTool::getInstance()->alertText(node, text ,size)

using namespace std;

struct AlertData
{
    Node *  node;
    string  text;
    int     size;
};

class AlertTextTool {
private:
    queue<AlertData>  m_alertData;
    
    
    
    AlertTextTool();
    ~AlertTextTool();
    
    void showNext();
    void removeText(Node * pSender);
public:
    static AlertTextTool * getInstance();
    void alertText(Node * node, string text, int size = 20);
    
};

#endif /* defined(__SwampAttack__AlertTextTool__) */
