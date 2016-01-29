//
//  GuideTextModel.cpp
//  SwampAttack
//
//  Created by oceantech02 on 16/1/26.
//
//

#include "GuideTextModel.hpp"


GuideTextModel::GuideTextModel(GuideTextInfo info)
{
    m_info = info;
    
    
}
GuideTextModel::~GuideTextModel()
{
    
}
void GuideTextModel::active()
{
    
}
void GuideTextModel::progress(float dlay)
{
    
}
void GuideTextModel::finish()
{
    
}

void GuideTextModel::setText(string _text)
{
    m_info.m_text = _text;
}