//
//  EnemySkill_fangyu.hpp
//  SwampAttack
//
//  Created by oceantech02 on 15/12/22.
//
//

#ifndef EnemySkill_fangyu_hpp
#define EnemySkill_fangyu_hpp

#include "EnemySkill.hpp"

class EnemySkill_fangyu : public EnemySkill {
    
public:
    EnemySkill_fangyu(string id);
    void    run(float timeStep);
    
};

#endif /* EnemySkill_fangyu_hpp */
