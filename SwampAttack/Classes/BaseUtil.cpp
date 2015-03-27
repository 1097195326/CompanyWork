//
//  BaseUtil.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/27.
//
//

#include "BaseUtil.h"

ActionInterval * BaseUtil::makeAnimateWithNameAndIndex(const std::string & name, int count)
{
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    auto animation = Animation::create();
    for (int i = 1; i <= count; ++i)
    {
//            char str[100] = {};
//            sprintf(str, "stone_hurt%002d.png",i);
            log("str: %s",StringUtils::format("%s%002d.png",name.c_str(),i).c_str());
        SpriteFrame * frame = spriteFrameCache->getSpriteFrameByName(
                                        StringUtils::format("%s%002d.png",name.c_str(),i));
        animation->addSpriteFrame(frame);
    }
    animation->setDelayPerUnit(0.1);
    return Animate::create(animation);
}
ActionInterval * BaseUtil::makeAnimateWithNameIndexDelay(const std::string & name, int count, float delay)
{
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    auto animation = Animation::create();
    for (int i = 1; i <= count; ++i)
    {
        SpriteFrame * frame = spriteFrameCache->getSpriteFrameByName(
                                                                     StringUtils::format("%s%002d.png",name.c_str(),i));
        animation->addSpriteFrame(frame);
    }
    animation->setDelayPerUnit(delay);
    return Animate::create(animation);
}