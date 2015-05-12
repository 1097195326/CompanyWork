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
    
    int     getSelectIndex();
    int     getControllerSize();
public:
    SelectMenuView(int num);
    virtual ~SelectMenuView();
    
    virtual bool    touchBegan(Touch * touch, Event * event);
    virtual void    touchMoved(Touch * touch, Event * event);
    virtual void    touchEnd(Touch * touch, Event * event);
    
};

#endif /* defined(__SwampAttack__SelectMenuView__) */
