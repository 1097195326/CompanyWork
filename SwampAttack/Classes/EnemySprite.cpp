//
//  EnemySprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "EnemySprite.h"
#include "BaseUtil.h"


EnemySprite::EnemySprite()
{
    m_map.insert(std::pair<std::string, Action*>("stone_walk",m_walkAction));
}
EnemySprite::~EnemySprite()
{
    m_map.clear();
    delete &m_map;
    
}
bool EnemySprite::init()
{
    if (!Sprite::init()) {
        return false;
    }
    return true;
}
void EnemySprite::createActionsWithFileName(const std::string &name)
{
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    
    //------ 此处可以移到 loading 中
    spriteFrameCache->addSpriteFramesWithFile(
                      StringUtils::format("image/%s.plist",name.c_str()),
                      StringUtils::format("image/%s.png",name.c_str())
                                              );
    m_walkAction = m_map["stone_walk"];
    m_walkAction = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex(name, 5));
    m_walkAction->retain();
//    m_map.insert(std::pair<std::string, Action*>("name",m_walkAction));
}
void EnemySprite::setMode(Enemy *model)
{
    m_model = model;
}
void EnemySprite::move()
{
    if (m_walkAction) {
        // 这 可能有其他操作：停止其他动画
        runAction(m_walkAction);
    }
}
void EnemySprite::hurt()
{
    if (m_hurtAction) {
        // 这 可能有其他操作：停止其他动画
        runAction(m_hurtAction);
    }
}