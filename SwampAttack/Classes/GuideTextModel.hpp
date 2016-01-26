//
//  GuideTextModel.hpp
//  SwampAttack
//
//  Created by oceantech02 on 16/1/26.
//
//

#ifndef GuideTextModel_hpp
#define GuideTextModel_hpp

#include "GuideBaseModel.hpp"

class GuideTextModel : public GuideBaseModel {
private:
    
public:
    GuideTextModel();
    ~GuideTextModel();
    
    void    active();
    void    progress();
    void    finish();
};

#endif /* GuideTextModel_hpp */
