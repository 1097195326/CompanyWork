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



struct GuideTextInfo
{
    string  m_id;
    string  m_text;
    bool    isAuto;
    
};

class GuideTextModel : public GuideBaseModel {
private:
    GuideTextInfo m_info;
    
    
public:
    GuideTextModel(GuideTextInfo info);
    ~GuideTextModel();
    
    void    active();
    void    progress(float dlay);
    void    finish();
    
    void    setText(string _text);
    
};

#endif /* GuideTextModel_hpp */
