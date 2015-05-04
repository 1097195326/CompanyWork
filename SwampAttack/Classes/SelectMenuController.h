//
//  SelectMenuController.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/4.
//
//

#ifndef __SwampAttack__SelectMenuController__
#define __SwampAttack__SelectMenuController__

enum SelectMenuStatus
{
    s_m_normal,
    s_m_select,
};

struct SelectMenu{
    SelectMenuStatus status = s_m_normal;
};

class SelectMenuController {
private:
    std::vector<SelectMenu> m_menus;
    
public:
    SelectMenuController();
    ~SelectMenuController();
public:     // interface
    void    setControllerSize(int size);
    int     getControllerSize();
    void    selectMenu(int index);
    int     getSelectIndex();
};

#endif /* defined(__SwampAttack__SelectMenuController__) */
