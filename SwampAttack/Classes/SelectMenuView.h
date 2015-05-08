//
//  SelectMenuView.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#ifndef __SwampAttack__SelectMenuView__
#define __SwampAttack__SelectMenuView__

#include "BaseCode.h"
#include "SelectMenuController.h"
#include "GameSubject.h"


class SelectMenuView : public Node, public GameSubject {
protected:
    SelectMenuController * m_controller;
    int     m_num;
    
    std::vector<Sprite *> m_normalSprites;
    std::vector<Sprite *> m_selectSprites;
    
public:
    virtual void    setNormalSprite(std::string name) = 0;
    virtual void    setSelectSprite(std::string name) = 0;
public:
    SelectMenuView(int num);
    ~SelectMenuView();
    
};

#endif /* defined(__SwampAttack__SelectMenuView__) */
