//
//  GuideClickModel.cpp
//  SwampAttack
//
//  Created by oceantech02 on 16/1/26.
//
//

#include "GuideClickModel.hpp"

GuideClickModel::GuideClickModel(GuideClickInfo info)
{
    
}
GuideClickModel::~GuideClickModel()
{
    
}
void GuideClickModel::active()
{
    
}
void GuideClickModel::progress(float dlay)
{
    
}
void GuideClickModel::finish()
{
    
}

void GuideClickModel::setClickRext(cocos2d::Rect _rect)
{
    m_info.m_rect = _rect;
}
bool GuideClickModel::clickPoint(cocos2d::Vec2 point)
{
    return m_info.m_rect.containsPoint(point);
}