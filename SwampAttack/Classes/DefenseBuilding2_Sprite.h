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
#include "DefenseBuildingSprite.h"

enum Defense2State
{
    d2_normal,
    d2_wait,
    d2_hurting,
};

class DefenseBuilding2_Sprite : public DefenseBuildingSprite {
private:
    Defense2State m_state;
    
    Sprite *  m_buildingS ;
    Action * attackAction;
    Action * waitAction ;
public:
    DefenseBuilding2_Sprite(DefenseBuilding * building);
    ~DefenseBuilding2_Sprite();
    void update(float data);
    
    void    attackCall();
    void    palyEndCall();
    void    attackPlay();
    void    waitPlay();
};

#endif /* defined(__SwampAttack__DefenseBuilding2_Sprite__) */
