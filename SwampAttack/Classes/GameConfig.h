//
//  GameConfig.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#ifndef SwampAttack_GameConfig_h
#define SwampAttack_GameConfig_h

#define GameLanguage "zh_CN" // 1
//#define GameLanguage "zh_EN" // 2

#define FONT 1

#if FONT == 1
    #define FontPath "fonts/mimi.ttf"

    #define healthNoEnough "体力不够"
    #define goldNoEnough "金币不够"
    #define guanqiaIslock "关卡未解锁"
#elif FONT == 2
    #define FontPath "fonts/AlertNotice.ttf"

    #define healthNoEnough "power is not enough"
    #define goldNoEnough "gold is not enough"
    #define guanqiaIslock "it is lock"
#endif


#endif
