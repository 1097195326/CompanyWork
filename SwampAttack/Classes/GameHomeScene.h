//
//  GameHomeScene.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/5.
//
//

#ifndef __SwampAttack__GameHomeScene__
#define __SwampAttack__GameHomeScene__

#include "BaseCode.h"

class GameHomeScene : public Layer {
private:
    
public:
    static Scene * scene();
    CREATE_FUNC(GameHomeScene);
    
    bool init();
    
    void    toMapScene(Ref * pSender);
    void    toShopScene(Ref * pSender);
    void    settingFunc(Ref * pSender);
    void    jiangbeiFunc(Ref * pSender);
    
};

#endif /* defined(__SwampAttack__GameHomeScene__) */
