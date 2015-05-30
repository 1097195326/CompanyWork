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

class MapGuanqiaButton : public Sprite, public GameObserver {
private:
    int     m_sceneIndex;
    int     m_index;
    
    MenuItem * m_menuItem;
    
public:
    
    MapGuanqiaButton(int sceneIndex, int index);
    ~MapGuanqiaButton();
    
    void    pressGuanqiaButtonFunc(Ref * pSender);
    void    updateData();
};

#endif /* defined(__SwampAttack__MapGuanqiaButton__) */
