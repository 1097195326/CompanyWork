//
//  EnemySkill_kuangbao.hpp
//  SwampAttack
//
//  Created by oceantech02 on 15/12/22.
//
//

#ifndef EnemySkill_kuangbao_hpp
#define EnemySkill_kuangbao_hpp

#include "EnemySkill.hpp"


class EnemySkill_kuangbao : public EnemySkill {
private:
    bool    isBegain;
public:
    EnemySkill_kuangbao(string id);
    void    run(float timeStep);
    
};

#endif /* EnemySkill_kuangbao_hpp */
