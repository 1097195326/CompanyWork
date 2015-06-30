//
//  SelectMenuView.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#include "SelectMenuView.h"

SelectMenuView::SelectMenuView(int num):m_num(num)
{
    m_controller = new SelectMenuController();
    m_controller->setControllerSize(m_num);
    
    m_normalSprites.reserve(num);
    m_selectSprites.reserve(num);
    
}
SelectMenuView::~SelectMenuView()
{
//    log("delete menu view");
    delete m_controller;
    m_normalSprites.clear();
    m_selectSprites.clear();
}
bool SelectMenuView::touchBegan(Touch *touch, Event *event)
{
        log("touch");
    return false;
}
void SelectMenuView::touchMoved(Touch *touch, Event *event)
{
    
}
void SelectMenuView::touchEnd(Touch *touch, Event *event)
{
    
}
int SelectMenuView::getSelectIndex()
{
    return m_controller->getSelectIndex();
}
int SelectMenuView::getControllerSize()
{
    return m_controller->getControllerSize();
}