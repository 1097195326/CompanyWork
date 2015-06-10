//
//  BaseUtil.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/27.
//
//

#ifndef __SwampAttack__BaseUtil__
#define __SwampAttack__BaseUtil__

#include "BaseCode.h"

namespace BaseUtil
{
    ActionInterval  *    makeAnimateWithNameAndIndex(const std::string & name, int count);
    ActionInterval  *    makeAnimateWithSprite(const std::string & name, int count);
    ActionInterval  *    makeAnimateWithNameIndexDelay(const std::string & name, int count, float delay);
    
    void addGray(Sprite* sp);
    void removeGray(Sprite* sp);
}



#endif /* defined(__SwampAttack__BaseUtil__) */
