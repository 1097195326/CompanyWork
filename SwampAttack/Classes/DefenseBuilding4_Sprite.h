//
//  DefenseBuilding4_Sprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/19.
//
//

#ifndef __SwampAttack__DefenseBuilding4_Sprite__
#define __SwampAttack__DefenseBuilding4_Sprite__

#include "BaseCode.h"
#include "DefenseBuilding.h"


class DefenseBuilding4_Sprite : public Sprite {
private:
    DefenseBuilding * m_building;
    
public:
    void    setModel(DefenseBuilding * building);
    bool    init();
    void    update(float data);
};

#endif /* defined(__SwampAttack__DefenseBuilding4_Sprite__) */
