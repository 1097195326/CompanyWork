//
//  SelectMenuController.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/4.
//
//

#include "SelectMenuController.h"

SelectMenuController::SelectMenuController()
{
    m_menus.reserve(6);
}
SelectMenuController::~SelectMenuController()
{
    
}
void SelectMenuController::setControllerSize(int size)
{
    for (int i = 0; i < size; ++i) {
        SelectMenu menu;
        if (i == 0) {
            menu.status = s_m_select;
        }
        m_menus.push_back(menu);
    }
}
int SelectMenuController::getControllerSize()
{
    return (int)m_menus.size();
}
void SelectMenuController::selectMenu(int index)
{
    for (int i = 0; i < m_menus.size(); i++) {
        m_menus[i].status = s_m_normal;
        if (i == index) {
            m_menus[i].status = s_m_select;
        }
    }
}
int SelectMenuController::getSelectIndex()
{
    int index;
    for (int i = 0; i < m_menus.size(); ++i) {
        if (m_menus[i].status == s_m_select) {
            index = i;
            break;
        }
    }
    return index;
}