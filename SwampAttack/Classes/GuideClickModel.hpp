//
//  GuideClickModel.hpp
//  SwampAttack
//
//  Created by oceantech02 on 16/1/26.
//
//

#ifndef GuideClickModel_hpp
#define GuideClickModel_hpp

#include "GuideBaseModel.hpp"

class GuideClickModel : public GuideBaseModel{
private:
    
public:
    GuideClickModel();
    ~GuideClickModel();
    
    void    active();
    void    progress();
    void    finish();
    
};

#endif /* GuideClickModel_hpp */
