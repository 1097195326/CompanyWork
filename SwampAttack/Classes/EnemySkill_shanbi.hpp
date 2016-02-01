//
//  EnemySkill_shanbi.hpp
//  SwampAttack
//
//  Created by oceantech02 on 15/12/22.
//
//

#ifndef EnemySkill_shanbi_hpp
#define EnemySkill_shanbi_hpp

#include "EnemySkill.hpp"

class EnemySkill_shanbi : public EnemySkill {
private:
    float   m_step;
public:
    EnemySkill_shanbi(string id);
    void    run(float timeStep);
    
};

#endif /* EnemySkill_shanbi_hpp */
