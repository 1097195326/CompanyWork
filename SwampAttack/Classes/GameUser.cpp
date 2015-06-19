//
//  GameUser.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#include "GameUser.h"

GameUser::GameUser():m_time(0)
{
    m_user = UserDefault::getInstance();
    if (!m_user->getBoolForKey("first")) {
        setBoolForKey("first", true);
        
        setUserGold(90000);
        m_userHealth = 5;
        setUserHealth(m_userHealth);
        unlockGuanqia("400001_1");
    }
    setUserGold(900000);
    m_userHealth = getUserHealth();
    
    enterGame();
    
    Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(GameUser::updateTime), this, 1, false);
    
    
}
GameUser::~GameUser()
{
//    Director::getInstance()->
}
GameUser * GameUser::getInstance()
{
    static GameUser user;
    return &user;
}
void GameUser::updateTime(float data)
{
//    log("add game time");
    if (m_userHealth >= 5)
    {
        return;
    }
    ++m_time;
    if (m_time >= 600) {
        ++m_userHealth;
        m_time = 0;
        setUserHealth(m_userHealth);
        notify();
    }
}
void GameUser::enterGame()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    
    int shiJianCha = now.tv_sec - getTimeSec();
    
    m_userHealth += shiJianCha / 600;
    m_time = shiJianCha % 600;
    if (m_userHealth > 5)
    {
        m_userHealth = 5;
    }
    setUserHealth(m_userHealth);
}
void GameUser::exitGame()
{
    setTimeSec();
}
double GameUser::getTimeSec()
{
    return m_user->getDoubleForKey("user_time");
}
void GameUser::setTimeSec()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    m_user->setDoubleForKey("user_time", now.tv_sec);
}
void GameUser::setUserHealth(int health)
{
    setIntForKey("user_health", health);
}
int GameUser::getUserHealth()
{
    return m_userHealth;
}
void GameUser::setUserGold(int gold)
{
    setIntForKey("user_gold", gold);
}
int GameUser::getUserGold()
{
    return getIntForKey("user_gold");
}
//--- expend prop
void GameUser::setExpendPropNum(int num)
{
    setIntForKey("user_expend_prop", num);
}
int GameUser::getExpendPropNum()
{
    return getIntForKey("user_expend_prop");
}
//--- guan qia ---
void GameUser::unlockGuanqia(string guanqiaId)
{
    setBoolForKey(guanqiaId + "guanqia", true);
}
bool GameUser::isUnlockGuanqia(string guanqiaId)
{
    return getBoolForKey(guanqiaId + "guanqia");
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
void GameUser::setTakeUpGun(string gunId,bool takeUp)
{
    setBoolForKey(gunId + "guntakeup", takeUp);
}
bool GameUser::isTakeUpGun(string gunId)
{
    return getBoolForKey(gunId + "guntakeup");
}
void GameUser::setTakeUpGunIndex(string gunId, int index)
{
    setIntForKey(gunId + "gunTakeUpIndex", index);
}
int GameUser::getTakeUpGunIndex(string gunId)
{
    return getIntForKey(gunId + "gunTakeUpIndex");
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
void GameUser::setPropNum(string propId, int num)
{
    setIntForKey(propId + "propNum", num);
}
int GameUser::getPropNum(string propId)
{
    return getIntForKey(propId + "propNum");
}
void GameUser::setTakeUpProp(string propId, bool takeUp)
{
    setBoolForKey(propId + "proptakeup", takeUp);
}
bool GameUser::isTakeUpProp(string propId)
{
    return getBoolForKey(propId + "proptakeup");
}
void GameUser::setTakeUpPropIndex(string propId, int index)
{
    setIntForKey(propId + "propTakeUpIndex", index);
}
int GameUser::getTakeUpPropIndex(string propId)
{
    return getIntForKey(propId + "propTakeUpIndex");
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