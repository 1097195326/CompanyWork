//
//  DefenseBuilding3_Sprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/19.
//
//

#ifndef __SwampAttack__DefenseBuilding3_Sprite__
#define __SwampAttack__DefenseBuilding3_Sprite__

#include "BaseCode.h"
#include "DefenseBuildingSprite.h"

enum Defense3State
{
    d3_normal,
    d3_wait,
    d3_hurting,
};

class DefenseBuilding3_Sprite : public DefenseBuildingSprite {
private:
    
    Defense3State m_state;
    
    Sprite *  m_buildingS ;
    Action * attackAction;
    Action * waitAction ;
public:
    DefenseBuilding3_Sprite(DefenseBuilding * building);
    ~DefenseBuilding3_Sprite();
    
    void    attackCall();
    void    palyEndCall();
    void    attackPlay();
    void    waitPlay();
    void    update(float data);
    
};

#endif /* defined(__SwampAttack__DefenseBuilding3_Sprite__) */
