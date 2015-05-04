//
//  ScrollController.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/4.
//
//

#include "ScrollController.h"


ScrollController::ScrollController():
m_vertical(false),
m_horizontal(false)
{
    
    
}
ScrollController::~ScrollController()
{
    
}
void ScrollController::update(float data)
{
    if (false) {
        
    }
    M_Vec2f force;
    if (m_offSet.x > m_contentWidth - m_viewWidth) {
        force.x = m_offSet.x - (m_contentWidth - m_viewWidth);
        
    }
    
    M_Vec2f normalForce = multMV(m_velocity, 0.1);
    
    m_velocity.add(normalForce);
    m_velocity.add(force);
    
    M_Vec2f change = multMV(m_velocity, data);
    
    m_offSet.add(change);
    
}
void ScrollController::updateOffSet(float ox, float oy)
{
    M_Vec2f m = M_Vec2f(ox,oy);
    m.mult(20);
    m_velocity.add(m);
}
void ScrollController::setHorizontal(bool canH)
{
    m_horizontal = canH;
}
void ScrollController::setVertical(bool canV)
{
    m_vertical = canV;
}
void ScrollController::setViewWidth(float width)
{
    m_viewWidth = width;
}
void ScrollController::setViewHeight(float height)
{
    m_viewHeight = height;
}
void ScrollController::setContentWidth(float width)
{
    m_contentWidth = width;
}
void ScrollController::setContentHeight(float height)
{
    m_contentHeight = height;
}