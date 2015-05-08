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
    
}
SelectMenuView::~SelectMenuView()
{
    
}