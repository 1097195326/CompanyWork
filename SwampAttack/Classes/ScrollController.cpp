//
//  ScrollController.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/4.
//
//

#include "ScrollController.h"

#include "BaseCode.h"

ScrollController::ScrollController():
m_vertical(false),
m_horizontal(false),
m_undulate(true),
m_isMoving(false),
m_isMoveToing(false),
m_centerPoint(leftTop)
{
    
    
}
ScrollController::~ScrollController()
{
    
}
void ScrollController::update(float data)
{
    
    if (m_isMoveToing)
    {
        
        M_Vec2f force;
        force.x = m_toOffSet.x - m_offSet.x;
        force.y = m_toOffSet.y - m_offSet.y;
        
//        printf("--:%f\n",force.x);
        if (force.x < 0 && force.x > -1) {
            m_isMoveToing = false;
            m_offSet.x = m_toOffSet.x;
            return;
        }else if (force.x > 0 && force.x < 1)
        {
            m_isMoveToing = false;
            m_offSet.x = m_toOffSet.x;
            return;
        }
        
        force.mult(0.3);
        m_offSet.add(force);
        force.mult(0);
        
    }
    
    M_Vec2f normalForce = multMV(m_velocity, -0.1);
    m_velocity.add(normalForce);
    M_Vec2f change = multMV(m_velocity, data);
    m_offSet.add(change);
    
    if (m_undulate)
    {
        M_Vec2f     force;
        if (m_offSet.x < m_viewWidth - m_contentWidth)
        {
            force.x = (m_viewWidth - m_contentWidth - m_offSet.x) * 0.1;
        }else if (m_offSet.x > 0.0)
        {
            force.x = (0.0 - m_offSet.x) * 0.1;
        }
        if (m_centerPoint == leftTop) {
            if (m_offSet.y > m_contentHeight - m_viewHeight)
            {
                force.y = (m_contentHeight - m_viewHeight - m_offSet.y) * 0.1;
            }else if (m_offSet.y < 0.0)
            {
                force.y = (0.0 - m_offSet.y) * 0.1;
            }
        }
        if (m_centerPoint == leftBottom) {
            if (m_offSet.y < m_viewHeight - m_contentHeight)
            {
                force.y = (m_viewHeight - m_contentHeight - m_offSet.y) * 0.1;
            }else if (m_offSet.y > 0.0)
            {
                force.y = (0.0 - m_offSet.y) * 0.1;
            }
        }
        if (m_isMoving)
        {
            m_force.x /= (std::fabs(force.x) > 1 ? std::fabs(force.x) : 1.0f);
            m_force.y /= (std::fabs(force.y) > 1 ? std::fabs(force.y) : 1.0f);
            m_offSet.add(m_force);
            m_force.mult(0);
        }else
        {
            m_offSet.add(force);
        }
    }else
    {
        m_offSet.add(m_force);
        m_force.mult(0);
        if (m_offSet.x < m_viewWidth - m_contentWidth)
        {
            m_offSet.x = (m_viewWidth - m_contentWidth);
        }else if (m_offSet.x > 0.0)
        {
            m_offSet.x = 0.0;
        }
        if (m_centerPoint == leftTop) {
            if (m_offSet.y > m_contentHeight - m_viewHeight)
            {
                m_offSet.y = m_contentHeight - m_viewHeight;
            }else if (m_offSet.y < 0.0)
            {
                m_offSet.y = 0.0;
            }
        }
        if (m_centerPoint == leftBottom) {
            if (m_offSet.y < m_viewHeight - m_contentHeight)
            {
                m_offSet.y = m_viewHeight - m_contentHeight;
            }else if (m_offSet.y > 0.0)
            {
                m_offSet.y = 0.0;
            }
        }
    }
}
void ScrollController::updateOffSet(float ox, float oy)
{
    if (!m_horizontal) {
        ox = 0.0;
    }
    if (!m_vertical) {
        oy = 0.0;
    }
    m_isMoving = true;
    M_Vec2f m = M_Vec2f(ox,oy);
    m_force = m;
//    m_offSet.add(m);
}
void ScrollController::updateVelocity(float ox, float oy)
{
    if (!m_horizontal) {
        ox = 0.0;
    }
    if (!m_vertical) {
        oy = 0.0;
    }
    m_isMoving = false;
    M_Vec2f m = M_Vec2f(ox,oy);
    m.mult(100);
    m_velocity.add(m);
}
void ScrollController::moveToOffSet(float ox, float oy)
{
    if (m_isMoveToing) {
        return;
    }
//    m_velocity.mult(0);
    m_isMoveToing = true;
    
//    printf("x:%f,y:%f\n",m_offSet.x,m_offSet.y);
//    printf("ox :%f,y:%f\n",ox,oy);
    
    m_toOffSet.x = ox;// - m_offSet.x;
    m_toOffSet.y = oy;// - m_offSet.y;

//    m_velocity.x = ox - m_offSet.x;
//    m_velocity.y = oy - m_offSet.y;
//    
//    m_velocity.mult(1.0f / MoveToTime);
//    m_velocity = juli;
    
}
void ScrollController::toOffSet(float ox, float oy)
{
    m_offSet.x = ox;
    m_offSet.y = oy;
}
M_Vec2f ScrollController::getOffSet()
{
    return m_offSet;
}
void ScrollController::setCenterPoint(CenterPoint point)
{
    m_centerPoint = point;
}
void ScrollController::setHorizontal(bool canH)
{
    m_horizontal = canH;
}
void ScrollController::setVertical(bool canV)
{
    m_vertical = canV;
}
void ScrollController::setUndulate(bool undulate)
{
    m_undulate = undulate;
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