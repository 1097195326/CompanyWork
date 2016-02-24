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
#include "DefenseBuildingSprite.h"

enum Defense4State
{
    d4_normal,
    d4_wait,
    d4_hurting,
};

class DefenseBuilding4_Sprite : public DefenseBuildingSprite {
private:
    Defense4State m_state;
    std::vector<Sprite *> m_buildingS;
    std::vector<Action *> m_attackActions;
    std::vector<Action *> m_waitActions;
    
    int     playIndex;
public:
    DefenseBuilding4_Sprite(DefenseBuilding * building);
    ~DefenseBuilding4_Sprite();
    
    void    update(float data);
    
    void    attackCall();
    void    palyEndCall();
    void    attackPlay();
    void    waitPlay();
};

#endif /* defined(__SwampAttack__DefenseBuilding4_Sprite__) */
