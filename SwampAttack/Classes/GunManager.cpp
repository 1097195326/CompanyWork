//
//  GunManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/30.
//
//

#include "GunManager.h"


GunManager::GunManager()
{
    
}
GunManager::~GunManager()
{
    
}
GunManager * GunManager::getInstance()
{
    static GunManager gunManager;
    return &gunManager;
}

void GunManager::gameLoop(float data)
{
    
}