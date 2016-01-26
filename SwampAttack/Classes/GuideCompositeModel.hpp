//
//  GuideCompositeModel.hpp
//  SwampAttack
//
//  Created by oceantech02 on 16/1/26.
//
//

#ifndef GuideCompositeModel_hpp
#define GuideCompositeModel_hpp

#include "GuideBaseModel.hpp"

using namespace std;

class GuideCompositeModel : public GuideBaseModel {
protected:
    list<GuideBaseModel *>  m_childModel;
    
public:
    GuideCompositeModel();
    ~GuideCompositeModel();
    
    void active();
    void progress();
    void finish();
    
    
    
};

#endif /* GuideCompositeModel_hpp */
