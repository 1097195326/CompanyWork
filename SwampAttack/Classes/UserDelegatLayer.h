//
//  UserDelegatLayer.h
//  SwampAttack
//
//  Created by 张洪星 on 15/7/5.
//
//

#ifndef __SwampAttack__UserDelegatLayer__
#define __SwampAttack__UserDelegatLayer__

#include "BaseCode.h"
#include "GameObserver.h"

class UserDelegateLayer : public Layer,public GameObserver
{
private:
    
    std::vector<Sprite *> m_healthSprites;
    Label   * m_goldLabel;
    Label   * m_expendPropLabel;
    
public:
    UserDelegateLayer();
    virtual ~UserDelegateLayer();
    
    
    void    healthPlusFunc(Ref * pSender);
    void    goldPlusFunc(Ref * pSender);
    void    expendPlusFunc(Ref * pSender);
    
    void updateUserData();
    
    void    updateData();
};

#endif /* defined(__SwampAttack__UserDelegatLayer__) */
