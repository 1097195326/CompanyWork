//
//  DefenseBuilding2_Sprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/19.
//
//

#ifndef __SwampAttack__DefenseBuilding2_Sprite__
#define __SwampAttack__DefenseBuilding2_Sprite__

#include "BaseCode.h"
#include "DefenseBuilding.h"


class DefenseBuilding2_Sprite : public Sprite {
private:
    DefenseBuilding * m_building;
public:
    bool init();
    void    setModel(DefenseBuilding * building);
    void update(float data);
};

#endif /* defined(__SwampAttack__DefenseBuilding2_Sprite__) */
