//
//  EnemySkill_yuancheng.hpp
//  SwampAttack
//
//  Created by oceantech02 on 15/12/22.
//
//

#ifndef EnemySkill_yuancheng_hpp
#define EnemySkill_yuancheng_hpp

#include "EnemySkill.hpp"

class EnemySkill_yuancheng : public EnemySkill {
private:
    float   m_timeStep;
public:
    EnemySkill_yuancheng(string id);
    void    run(float timeStep);
    void doDone();
};

#endif /* EnemySkill_yuancheng_hpp */
