//
//  UserGuideManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 16/1/26.
//
//

#include "UserGuideManager.hpp"


UserGuideManager::UserGuideManager()
{
    
}
UserGuideManager::~UserGuideManager()
{
    
}
UserGuideManager * UserGuideManager::getInstance()
{
    static UserGuideManager userGuideManager;
    return &userGuideManager;
}
void UserGuideManager::gameLoop(float dlay)
{
    
}
