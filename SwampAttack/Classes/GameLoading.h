//
//  GameLoading.h
//  SwampAttack
//
//  Created by oceantech02 on 15/4/13.
//
//

#ifndef __SwampAttack__GameLoading__
#define __SwampAttack__GameLoading__

#include "BaseCode.h"

#include "json/json.h"

class GameLoading {
private:
    
public:
    static float loadSprites();
    static float loadFrames();
    static float loadFramesByData(Json::Value data);
};

#endif /* defined(__SwampAttack__GameLoading__) */
