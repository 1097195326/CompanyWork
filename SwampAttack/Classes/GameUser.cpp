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
void GameUser::setUserGold(int gold)
{
    setIntForKey("user_gold", gold);
}
int GameUser::getUserGold()
{
    return getIntForKey("user_gold");
}
void GameUser::unlockGun(string gunId)
{
    setBoolForKey(gunId, true);
}
bool GameUser::isUnlockGun(string gunId)
{
    return getBoolForKey(gunId);
}
void GameUser::setGunLevel(string gunId, int level)
{
    setIntForKey(gunId + "_level", level);
}
int GameUser::getGunLevel(string gunId)
{
    return getIntForKey(gunId + "_level");
}
void GameUser::setGunBulletNumber(string gunId, int num)
{
    setIntForKey(gunId + "_bullet", num);
}
int GameUser::getGunBulletNumber(string gunId)
{
    return getIntForKey(gunId + "_bullet");
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
void GameUser::setStringForKey(string name, string value)
{
    m_user->setStringForKey(name.c_str(), value);
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
string GameUser::getStringForKey(string name)
{
    return m_user->getStringForKey(name.c_str());
}