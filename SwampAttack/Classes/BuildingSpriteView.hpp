//
//  BuildingSpriteView.hpp
//  SwampAttack
//
//  Created by oceantech02 on 16/2/22.
//
//

#ifndef BuildingSpriteView_hpp
#define BuildingSpriteView_hpp

#include "BaseCode.h"
#include "DefenseBuilding.h"
#include "GameObserver.h"
#include "ProgressBar.h"

class BuildingSpriteView : public Sprite,public GameObserver{
private:
    DefenseBuilding * m_building;
    ProgressBar * m_numProBar;
    Sprite  *   m_greenBg;
    Sprite  *   m_blueBg;
    EventListenerTouchOneByOne * m_listener;
    float   m_iconScale;
    
public:
    BuildingSpriteView(DefenseBuilding * building);
    ~BuildingSpriteView();
    void updateData();
    
    bool    touchBegan(Touch * touch, Event * event);
    void    touchEnd(Touch * touch, Event * event);
};


#endif /* BuildingSpriteView_hpp */
