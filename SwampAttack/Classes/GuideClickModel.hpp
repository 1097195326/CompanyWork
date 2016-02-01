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
#include "BaseCode.h"


struct GuideClickInfo
{
    string  m_id;
    Rect    m_rect;
};

class GuideClickModel : public GuideBaseModel{
private:
    GuideClickInfo  m_info;
    
    
public:
    GuideClickModel(GuideClickInfo info);
    ~GuideClickModel();
    
    void    active();
    void    progress(float dlay);
    void    finish();
public:
    void    setClickRext(Rect _rect);
    bool    clickPoint(Vec2 point);
    
};

#endif /* GuideClickModel_hpp */
