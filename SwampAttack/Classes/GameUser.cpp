//
//  GameUser.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#include "GameUser.h"
#include "GuanggaoManager.hpp"


GameUser::GameUser():
m_time(0),
m_guanggaoTime(0),
m_guanggaoAddTime(0),
m_isGuiding(false)
{
    m_user = UserDefault::getInstance();
    if (!m_user->getBoolForKey("first")) {
        setBoolForKey("first", true);
        
        setUserGold(1000);
        m_userHealth = FullHealth;
        setUserHealth(m_userHealth);
        setExpendPropNum(3);
        unlockGuanqia("400001_1");
        setLastGuanqiaIndex(1);
        setLastSceneIndex(1);
    }
//    setUserGold(900000);
//    unlockGuanqia("400004_5");
//    setUserHealth(0);
    m_guanggaoAddTime = _Gg_M_->getGuangggaoModelByIndex(getGuanggaoIndex())->getTime();
    
    m_userHealth = getIntForKey("user_health");
    
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
    if (!_Gg_M_->getGuangggaoModelByIndex(getGuanggaoIndex())->isReady())
    {
        ++m_guanggaoTime;
        if (m_guanggaoTime >= m_guanggaoAddTime)
        {
            m_guanggaoTime = 0;
            _Gg_M_->getGuangggaoModelByIndex(getGuanggaoIndex())->setReady(true);
        }
    }
    if (m_userHealth >= FullHealth)
    {
        return;
    }
    ++m_time;
//    log("time :%d",m_time);
    if (m_time >= _G_AddTime) {
        log("add health");
        ++m_userHealth;
        m_time = 0;
        setUserHealth(m_userHealth);
        notify();
    }
}
void GameUser::enterGame()
{
    log("game user enter game");
    struct timeval now;
    gettimeofday(&now, NULL);
    
    int shiJianCha = now.tv_sec - getTimeSec();
    
    if (shiJianCha / m_guanggaoAddTime >=1)
    {
        _Gg_M_->getGuangggaoModelByIndex(getGuanggaoIndex())->setReady(true);
    }else
    {
        m_guanggaoTime += shiJianCha % m_guanggaoAddTime;
    }
    
    m_userHealth += shiJianCha / _G_AddTime;
    m_time += shiJianCha % _G_AddTime;
    if (m_userHealth > FullHealth)
    {
        m_userHealth = FullHealth;
    }
    setUserHealth(m_userHealth);
    notify();
}
void GameUser::exitGame()
{
    log("game user exit game");
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
int GameUser::getTime()
{
    return m_time;
}
void GameUser::setIsHaveXinshouYindao()
{
    setBoolForKey("user_xinshou_yindao", true);
}
bool GameUser::isHaveXinshouYindao()
{
    return getBoolForKey("user_xinshou_yindao");
}
void GameUser::setUserHealth(int health)
{
    setIntForKey("user_health", health);
    setTimeSec();
}
int GameUser::getUserHealth()
{
    return m_userHealth;
}
void GameUser::useHealthTimes()
{
    --m_userHealth;
    setUserHealth(m_userHealth);
}
void GameUser::addHealthToFull()
{
    m_userHealth = FullHealth;
    setUserHealth(m_userHealth);
    notify();
}
void GameUser::setUserGold(int gold)
{
    setIntForKey("user_gold", gold);
    notify();
}
int GameUser::getUserGold()
{
    return getIntForKey("user_gold");
}
//--- expend prop
void GameUser::setExpendPropNum(int num)
{
    setIntForKey("user_expend_prop", num);
    notify();
}
int GameUser::getExpendPropNum()
{
    return getIntForKey("user_expend_prop");
}
bool GameUser::useExpendProp()
{
    int num = getExpendPropNum();
    if (num > 0) {
        --num;
        setExpendPropNum(num);
        return true;
    }
    return false;
}
//--- user guide
bool GameUser::isHaveGuide()
{
    return getBoolForKey("user_guide");
}
void GameUser::setIsHaveGuide()
{
    setIntForKey("user_guide", true);
}
bool GameUser::isGuiding()
{
    return m_isGuiding;
}
void GameUser::setIsGuiding(bool isOrN)
{
    m_isGuiding = isOrN;
}
//--- guang gao
int GameUser::getGuanggaoTime()
{
    return m_guanggaoTime;
}
void GameUser::setGuanggaoAddTime(int time)
{
    m_guanggaoAddTime = time;
}
void GameUser::setGuanggaoIndex(int index)
{
    setIntForKey("UserGuanggaoIndex", index);
}
int GameUser::getGuanggaoIndex()
{
    return getIntForKey("UserGuanggaoIndex");
}
//--- guan qia ---
void GameUser::setGuanqiaStarNum(string g_id,int num)
{
    setIntForKey(g_id + "guanqiaStar", num);
}
int GameUser::getGuanqiaStarNum(string g_id)
{
    return getIntForKey(g_id + "guanqiaStar");
}
void GameUser::setGuanqiaWin(string guanqiaId)
{
    setBoolForKey(guanqiaId + "guanqiaWin", true);
}
bool GameUser::isWinGuanqia(string guanqiaId)
{
    return getBoolForKey(guanqiaId + "guanqiaWin");
}
void GameUser::unlockGuanqia(string guanqiaId)
{
    setBoolForKey(guanqiaId + "guanqia", true);
}
bool GameUser::isUnlockGuanqia(string guanqiaId)
{
    return getBoolForKey(guanqiaId + "guanqia");
}
void GameUser::setLastSceneIndex(int index)
{
    setIntForKey("CurrentSceneIndex", index);
}
int GameUser::getLastSceneIndex()
{
    return getIntForKey("CurrentSceneIndex");
}
void GameUser::setLastGuanqiaIndex(int index)
{
    setIntForKey("CurrentGuanqiaIndex", index);
}
int GameUser::getLastGuanqiaIndex()
{
    return getIntForKey("CurrentGuanqiaIndex");
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
void GameUser::setBuildingJishu(string buildingId, int jishu)
{
    setIntForKey(buildingId + "buildingJishu", jishu);
}
int GameUser::getBuildingJishu(string buildingId)
{
    return getIntForKey(buildingId + "buildingJishu");
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
void GameUser::setPropLevel(string propId, int level)
{
    setIntForKey(propId + "propLevel", level);
}
int GameUser::getPropLevel(string propId)
{
    return getIntForKey(propId + "propLevel");
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