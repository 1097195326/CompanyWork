//
//  GameUser.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#include "GameUser.h"

GameUser::GameUser()
{
    m_user = UserDefault::getInstance();
}
GameUser::~GameUser()
{
    
}
GameUser * GameUser::getInstance()
{
    static GameUser user;
    return &user;
}
void GameUser::unlockGun(string gunId)
{
    setBoolForKey(gunId, true);
}
bool GameUser::isUnlockGun(string gunId)
{
    return getBoolForKey(gunId);
}
void GameUser::setGunDamage(string gunId,float damage)
{
    setFloatForKey(gunId, damage);
}
float GameUser::getGunDamage(string gunId)
{
    return getFloatForKey(gunId);
}
void GameUser::setGunBulletNumber(string bulletId, int num)
{
    setIntForKey(bulletId, num);
}
int GameUser::getGunBulletNumber(string bulletId)
{
    return getIntForKey(bulletId);
}

//----- private function
void GameUser::setBoolForKey(string name, bool value)
{
    m_user->setBoolForKey(name.c_str(), value);
    m_user->flush();
}
void GameUser::setIntForKey(string name, int value)
{
    m_user->setIntegerForKey(name.c_str(), value);
    m_user->flush();
}
void GameUser::setFloatForKey(string name, float value)
{
    m_user->setFloatForKey(name.c_str(), value);
    m_user->flush();
}
bool GameUser::getBoolForKey(string name)
{
    return m_user->getBoolForKey(name.c_str(), false);
}
int GameUser::getIntForKey(string name)
{
    return m_user->getIntegerForKey(name.c_str());
}
float GameUser::getFloatForKey(string name)
{
    return m_user->getFloatForKey(name.c_str());
}