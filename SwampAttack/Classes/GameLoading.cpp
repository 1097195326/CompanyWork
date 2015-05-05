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
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zomBieWait.plist"));
    //
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zomBieHurt.plist"));
    
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skullWalk.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skullAttack.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skullDown.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skullWait.plist"));
    
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrowWalk.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrowAttack.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrowDown.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrowWait.plist"));
    
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("pumpkinWalk.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("pumpkinAttack.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("pumpkinDown.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("pumpkinWait.plist"));
    
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("muroideaWalk.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("muroideaAttack.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("muroideaDown.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("muroideaWait.plist"));
    
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("batFly.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("batAttack.plist"));
    
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("crowFly.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("crowAttack.plist"));
    
    
}