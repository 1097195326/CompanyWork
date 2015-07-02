//
//  MapGuanqiaButton.h
//  SwampAttack
//
//  Created by 张洪星 on 15/5/30.
//
//

#ifndef __SwampAttack__MapGuanqiaButton__
#define __SwampAttack__MapGuanqiaButton__

#include "BaseCode.h"
#include "GameObserver.h"
#include "GameSprite.h"


class MapGuanqiaButton : public Sprite, public GameObserver {
private:
    int     m_sceneIndex;
    int     m_index;
    std::string  m_guanqiaId;
    
    
    GameSprite * m_menuItem;
    Sprite  *   m_lockSprite;
    
public:
    
    MapGuanqiaButton(int sceneIndex, int index);
    ~MapGuanqiaButton();
    
    void    pressGuanqiaButtonFunc(Touch * touch, Event * event);
    void    updateData();
};

#endif /* defined(__SwampAttack__MapGuanqiaButton__) */
