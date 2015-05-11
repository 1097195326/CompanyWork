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
    m_normalSprites.clear();
    m_selectSprites.clear();
}
bool SelectMenuView::touchBegan(Touch *touch, Event *event)
{
    //    log("touch");
    return false;
}
void SelectMenuView::touchMoved(Touch *touch, Event *event)
{
    
}
void SelectMenuView::touchEnd(Touch *touch, Event *event)
{
    
}