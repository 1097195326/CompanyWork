//
//  GuideCompositeApposeModel.hpp
//  SwampAttack
//
//  Created by oceantech02 on 16/1/26.
//
//

#ifndef GuideCompositeApposeModel_hpp
#define GuideCompositeApposeModel_hpp

#include "GuideCompositeModel.hpp"


class GuideCompositeApposeModel: public GuideCompositeModel {
private:
    
public:
    GuideCompositeApposeModel();
    ~GuideCompositeApposeModel();
    
    void active();
    void progress();
    void finish();
};

#endif /* GuideCompositeApposeModel_hpp */
