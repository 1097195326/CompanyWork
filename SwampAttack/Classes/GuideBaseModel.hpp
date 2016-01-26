//
//  GuideBaseModel.hpp
//  SwampAttack
//
//  Created by oceantech02 on 16/1/26.
//
//

#ifndef GuideBaseModel_hpp
#define GuideBaseModel_hpp

enum GuideModelStatus
{
    
    g_active      = 1 << 0,
    g_progress    = 1 << 1,
    g_finish      = 1 << 2,
    
};
class GuideBaseModel {
private:
    int     m_status;
    
public:
    GuideBaseModel();
    virtual ~GuideBaseModel();
    
    virtual void    active();
    virtual void    progress();
    virtual void    finish();
    
    bool    isActive();
    void    setActive();
    bool    isProgress();
    void    setProgress();
    bool    isFinish();
    void    setFinish();
};

#endif /* GuideBaseModel_hpp */
