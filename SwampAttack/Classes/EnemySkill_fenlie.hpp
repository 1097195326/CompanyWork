//
//  EnemySkill_fenlie.hpp
//  SwampAttack
//
//  Created by oceantech02 on 15/12/22.
//
//

#ifndef EnemySkill_fenlie_hpp
#define EnemySkill_fenlie_hpp

#include "EnemySkill.hpp"


class EnemySkill_fenlie : public EnemySkill {
private:
    bool    isFenlie;
public:
    EnemySkill_fenlie(string id);
    void    run(float timeStep);
    
};

#endif /* EnemySkill_fenlie_hpp */
