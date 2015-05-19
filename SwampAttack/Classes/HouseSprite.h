//
//  HouseSprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/4/29.
//
//

#ifndef __SwampAttack__HouseSprite__
#define __SwampAttack__HouseSprite__

#include "BaseCode.h"
#include "ProgressBar.h"
#include "House.h"


class HouseSprite : public Sprite {
private:
    House * m_houseModel;
    ProgressBar * m_healthBar;
    
private:
    void    initView();
public:
    void    setModel(House * house);
public:
    HouseSprite();
    ~HouseSprite();
    void    update(float data);
    
};

#endif /* defined(__SwampAttack__HouseSprite__) */
