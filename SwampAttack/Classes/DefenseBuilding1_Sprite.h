//
//  DefenseBuilding1_Sprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/19.
//
//

#ifndef __SwampAttack__DefenseBuilding1_Sprite__
#define __SwampAttack__DefenseBuilding1_Sprite__

#include "BaseCode.h"
#include "DefenseBuilding.h"


class DefenseBuilding1_Sprite : public Sprite {
private:
    DefenseBuilding * m_building;
public:
    bool    init();
    DefenseBuilding1_Sprite();
    
};

#endif /* defined(__SwampAttack__DefenseBuilding1_Sprite__) */
