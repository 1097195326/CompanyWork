//
//  MapScrollHeadler.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/29.
//
//

#include "MapScrollHeadler.h"
#include "MapGuanqiaButton.h"
#include "GuanQiaManager.h"



MapScrollHeadler::MapScrollHeadler(int sceneIndex)
{
    setIndex(sceneIndex);
    Sprite * bg = Sprite::create(ImagePath(StringUtils::format("map_scene%d.png",(m_index + 1))));
    addChild(bg);
    
    Vec2 offVec = Vec2(m_visibleOrigin.x - m_visibleSize.width * 0.5,
                   m_visibleOrigin.y - m_visibleSize.height * 0.5);
    
    for (int i = 1; i <= 10; ++i)
    {
        std::string guanqiaId = StringUtils::format("40000%d_%d",(m_index + 1),i);
        GuanqiaModel * guanQia = GuanQiaManager::getInstance()->getGuanqiaById(guanqiaId);
        
        MapGuanqiaButton * button = new MapGuanqiaButton(m_index,i);
        button->setPosition(offVec);
        button->autorelease();
        addChild(button);
        
        std::string shadeName = guanQia->getShadeName();
        if (shadeName.size() > 0)
        {
            std::string imageName;
            if (guanQia->isUnlock())
            {
                imageName = StringUtils::format("%s_light.png",shadeName.c_str());
            }else
            {
                imageName = StringUtils::format("%s.png",shadeName.c_str());
            }
            
            Vec2 yPoint = guanQia->getYinyingPoint();
            Sprite * yinying = Sprite::createWithSpriteFrameName(imageName);
            yinying->setPosition(offVec + yPoint);
            addChild(yinying);
//            log("%s:%f",imageName.c_str(),yPoint.x);
        }
    }
    
    
    
    
}
MapScrollHeadler::~MapScrollHeadler()
{
    
}


