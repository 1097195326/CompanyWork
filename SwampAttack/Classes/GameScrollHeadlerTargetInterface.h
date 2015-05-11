//
//  GameScrollHeadlerTargetInterface.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/11.
//
//

#ifndef __SwampAttack__GameScrollHeadlerTargetInterface__
#define __SwampAttack__GameScrollHeadlerTargetInterface__

#include "GameScrollHeadler.h"

struct GameScrollHeadlerTargetInterface {
     virtual GameScrollHeadler * getHeadlerByIndex(int index) = 0;
};

#endif /* defined(__SwampAttack__GameScrollHeadlerTargetInterface__) */
