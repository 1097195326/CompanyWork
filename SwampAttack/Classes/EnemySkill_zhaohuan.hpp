//
//  EnemySkill_zhaohuan.hpp
//  SwampAttack
//
//  Created by oceantech02 on 15/12/22.
//
//

#ifndef EnemySkill_zhaohuan_hpp
#define EnemySkill_zhaohuan_hpp

#include "EnemySkill.hpp"


class EnemySkill_zhaohuan : public EnemySkill {
private:
    float   m_timeStep;
public:
    EnemySkill_zhaohuan(string id);
    void    run(float timeStep);
    
};


#endif /* EnemySkill_zhaohuan_hpp */
