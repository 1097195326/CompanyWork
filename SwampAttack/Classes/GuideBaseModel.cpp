//
//  GuideBaseModel.cpp
//  SwampAttack
//
//  Created by oceantech02 on 16/1/26.
//
//

#include "GuideBaseModel.hpp"

GuideBaseModel::GuideBaseModel()
{
    
}
GuideBaseModel::~GuideBaseModel()
{
    
}
void GuideBaseModel::active()
{
    
}
void GuideBaseModel::progress()
{
    
}
void GuideBaseModel::finish()
{
    
}

// status

bool GuideBaseModel::isActive()
{
    return m_status & g_active;
}
void GuideBaseModel::setActive()
{
    m_status = g_active;
}
bool GuideBaseModel::isProgress()
{
    return m_status & g_progress;
}
void GuideBaseModel::setProgress()
{
    m_status = g_progress;
}
bool GuideBaseModel::isFinish()
{
    return m_status & g_finish;
}
void GuideBaseModel::setFinish()
{
    m_status = g_finish;
}