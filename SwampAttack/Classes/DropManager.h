//
//  DropManager.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/24.
//
//

#ifndef __SwampAttack__DropManager__
#define __SwampAttack__DropManager__

#include "DropModel.h"

class DropManager {
private:
    std::map<string,DropModel *>    m_dropData;
    std::map<int,std::string> m_hashHead;
    
    
    DropManager();
    ~DropManager();
public:
    static DropManager * getInstance();
    
    void    dropObject(string objId,Vec2 point);
    
};

#endif /* defined(__SwampAttack__DropManager__) */
