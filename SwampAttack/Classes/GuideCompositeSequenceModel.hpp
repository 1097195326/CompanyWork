//
//  GuideCompositeSequenceModel.hpp
//  SwampAttack
//
//  Created by oceantech02 on 16/1/26.
//
//

#ifndef GuideCompositeSequenceModel_hpp
#define GuideCompositeSequenceModel_hpp

#include "GuideCompositeModel.hpp"

class GuideCompositeSequenceModel: public GuideCompositeModel {
private:
    
public:
    GuideCompositeSequenceModel();
    ~GuideCompositeSequenceModel();
    
    void active();
    void progress();
    void finish();
};

#endif /* GuideCompositeSequenceModel_hpp */
