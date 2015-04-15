//
//  GameLoading.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/13.
//
//

#include "GameLoading.h"


float GameLoading::loadSprites()
{
    
}
float GameLoading::loadFrames()
{
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("reloadShotGun.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("runShotGun.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("shootShotGun.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("waitShotGun.plist"));
    
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zomBieWalk.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zomBieAttack.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zomBieDown.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zomBieHurt.plist"));
    
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zomBieWalk.plist"), ImagePath("zomBieWalk.png"));
    
    
}