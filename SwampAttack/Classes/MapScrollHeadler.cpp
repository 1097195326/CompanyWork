//
//  MapScrollHeadler.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/29.
//
//

#include "MapScrollHeadler.h"
#include "MapGuanqiaButton.h"



MapScrollHeadler::MapScrollHeadler(int sceneIndex)
{
    setIndex(sceneIndex);
    Sprite * bg = Sprite::create(ImagePath("map_scene1.png"));
    addChild(bg);
    
    for (int i = 1; i <= 10; ++i)
    {
        MapGuanqiaButton * button = new MapGuanqiaButton(m_index,i);
        button->setPosition(m_visibleOrigin.x - m_visibleSize.width * 0.5,
                            m_visibleOrigin.y - m_visibleSize.height * 0.5);
        button->autorelease();
        addChild(button,3);
    }
    
    
    
    
}
MapScrollHeadler::~MapScrollHeadler()
{
    
}


