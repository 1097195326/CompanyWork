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
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("qiang3.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("qiang3_2.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("qiang5.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("qiang7.plist"));
    
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zombie1.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zombie2.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zombie3.plist"));
    //
    
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skull1.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skull2.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skull3.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skull4.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skullArmor.plist"));
    
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrow1.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrow2.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrow3.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrow4.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrowArmor.plist"));
    
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolf1.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolf2.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolf3.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolf4.plist"));
    
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Pumpkin1.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Pumpkin2.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Pumpkin3.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Pumpkin4.plist"));
    
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Muroidea1.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Muroidea2.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Muroidea3.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Muroidea4.plist"));
    
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("bat.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("demon.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("crow.plist"));
    
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("explosion.plist"));
    
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("blind1.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("blind2.plist"));
    
    
    
}