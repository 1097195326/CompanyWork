//
//  MapGuanqiaButton.cpp
//  SwampAttack
//
//  Created by 张洪星 on 15/5/30.
//
//

#include "MapGuanqiaButton.h"
#include "GuanQiaManager.h"


MapGuanqiaButton::MapGuanqiaButton(int sceneIndex, int index):
m_sceneIndex(sceneIndex),
m_index(index)
{
    init();
    //400001_1
    std::string guanqiaId = StringUtils::format("40000%d_%d",(m_sceneIndex + 1),m_index);
//    log("guan qia id:%s",guanqiaId.c_str());
    
    GuanqiaModel * guanQia = GuanQiaManager::getInstance()->getGuanqiaById(guanqiaId);
    setSubject(guanQia);
    
    m_menuItem = MenuItemImage::create(ImagePath("map_button.png"),
                                       ImagePath("map_button.png"),
                                       CC_CALLBACK_1(MapGuanqiaButton::pressGuanqiaButtonFunc, this));
    m_menuItem->setPosition(guanQia->getGuanqiaPoint());
    Menu * buttonMenu = Menu::create(m_menuItem, NULL);
    buttonMenu->setPosition(Point::ZERO);
    addChild(buttonMenu);
    
    
}
MapGuanqiaButton::~MapGuanqiaButton()
{
    
}

void MapGuanqiaButton::updateData()
{
    
}
void MapGuanqiaButton::pressGuanqiaButtonFunc(cocos2d::Ref *pSender)
{
    log("button index : %d",m_index);
}
