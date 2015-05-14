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
//--- gun ---
void GameUser::unlockGun(string gunId)
{
    setBoolForKey(gunId + "gun", true);
}
bool GameUser::isUnlockGun(string gunId)
{
    return getBoolForKey(gunId + "gun");
}
void GameUser::setGunLevel(string gunId, int level)
{
    setIntForKey(gunId + "gunlevel", level);
}
int GameUser::getGunLevel(string gunId)
{
    return getIntForKey(gunId + "gunlevel");
}
void GameUser::setGunBulletNumber(string gunId, int num)
{
    setIntForKey(gunId + "gunbullet", num);
}
int GameUser::getGunBulletNumber(string gunId)
{
    return getIntForKey(gunId + "gunbullet");
}
//--- building ---
void GameUser::unlockBuilding(string buildingId)
{
    setBoolForKey(buildingId + "building", true);
}
bool GameUser::isUnlockBuilding(string buildingId)
{
    return getBoolForKey(buildingId + "building");
}
void GameUser::setBuildingLevel(string buildingId, int level)
{
    setIntForKey(buildingId + "buildingLevel", level);
}
int GameUser::getBuildingLevel(string buildingId)
{
    return getIntForKey(buildingId + "buildingLevel");
}
//--- prop ----
void GameUser::unlockProp(string propId)
{
    setBoolForKey(propId + "prop", true);
}
bool GameUser::isUnlockProp(string propId)
{
    return getBoolForKey(propId + "prop");
}
void GameUser::setPorpNum(string propId, int num)
{
    setIntForKey(propId + "propNum", num);
}
int GameUser::getPropNum(string propId)
{
    return getIntForKey(propId + "propNum");
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