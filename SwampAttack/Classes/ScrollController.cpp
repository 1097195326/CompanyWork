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
    if (m_offSet.x < m_viewWidth - m_contentWidth)
    {
        force.x = (m_viewWidth - m_contentWidth - m_offSet.x) * 0.2;
        
    }else if (m_offSet.x > 0.0)
    {
        force.x = (0.0 - m_offSet.x) * 0.2;
    }
    if (m_offSet.y < m_viewHeight - m_contentHeight)
    {
        force.y = (m_viewHeight - m_contentHeight - m_offSet.y) * 0.2;
    }else if (m_offSet.y > 0.0)
    {
        force.y = (0.0 - m_offSet.y) * 0.2;
    }
    
    M_Vec2f normalForce = multMV(m_velocity, -0.1);
    
    m_velocity.add(normalForce);
    m_velocity.add(force);
//    printf("m_velocity x:%f,y:%f \n",m_velocity.x,m_velocity.y);
    M_Vec2f change = multMV(m_velocity, data);
    m_offSet.add(change);
//    printf("m_offSet x:%f,y:%f \n",m_offSet.x,m_offSet.y);
}
void ScrollController::updateOffSet(float ox, float oy)
{
    if (!m_horizontal) {
        oy = 0.0;
    }
    if (!m_vertical) {
        ox = 0.0;
    }
    M_Vec2f m = M_Vec2f(ox,oy);
    m.mult(20);
    m_velocity.add(m);
}
M_Vec2f ScrollController::getOffSet()
{
    return m_offSet;
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