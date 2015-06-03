//
//  Prop.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/30.
//
//

#include "Prop.h"
#include "ConfigManager.h"
#include "GameUser.h"
#include "GameMapManager.h"
#include "Human.h"

#include "PropSprite_daoju1.h"
#include "PropSprite_daoju2.h"
#include "PropSprite_daoju3.h"
#include "PropSprite_daoju5.h"


Prop::Prop(Json::Value data):m_isUnlock(false),m_num(0)
{
    m_id = data["ItemId"].asString() ;
    string itemName = data["ItemName"].asString();
    m_itemName = _C_M->getTranslateById(itemName);
    m_modelId = data["ModelId"].asString();
    m_effectArea = atof(data["EffectArea"].asString().c_str());
    m_unlockMission = data["UnlockMission"].asString();
    m_unlockGold = atoi(data["UnlockGold"].asString().c_str());
    m_itemPrice = atoi(data["ItemPrice"].asString().c_str());
    m_damage =
    data["Damage"].asString() == "" ?
    0 : atof(data["Damage"].asString().c_str());
    m_percentageDamage =
    data["PercentageDamage"].asString() == "" ?
    0 : atof(data["PercentageDamage"].asString().c_str());
    
    m_buffIds.reserve(4);
    Json::Value buffIds = data["BuffId"];
    if (buffIds.size() > 0) {
        for (int i = 0; i< buffIds.size(); ++i)
        {
            m_buffIds.push_back(buffIds[i].asString());
        }
    }
    string itemDescription = data["ItemDescription"].asString();
    m_itemDestription = _C_M->getTranslateById(itemDescription);
    
    m_num = _G_U->getPropNum(m_id);
    m_isUnlock = _G_U->isUnlockProp(m_id);
    m_isTakeUp = _G_U->isTakeUpProp(m_id);
    m_takeUpIndex = _G_U->getTakeUpPropIndex(m_id);
}
Prop::~Prop()
{
    
}
void Prop::setFightView()
{
    if (m_modelId == "daoju1") {
        PropSprite * sprite = new PropSprite_daoju1(this);
        sprite->setSubject(this);
        sprite->autorelease();
    }else
    {
        PropSprite * sprite = new PropSprite(this);
        sprite->setSubject(this);
        sprite->autorelease();
    }
    
}
void Prop::gameLoop(float data)
{
//    if (isMoveEnd())
//    {
//        float arrveLine = _G_M_M->enemy_start_buttomPoint.y + _G_M_M->enemy_start_upline;
//        
//        if (m_point.y > arrveLine) {
//            
//        }else
//        {
//            
//        }
//    }
}
bool Prop::buyProp()
{
    int userGold = _G_U->getUserGold();
    if (userGold < m_itemPrice)
    {
        return false;
    }
    userGold -= m_itemPrice;
    _G_U->setUserGold(userGold);
    
    ++m_num;
    _G_U->setPropNum(m_id, m_num);
    notify();
    return true;
}
void Prop::takeUp(int index)
{
    m_isTakeUp = true;
    m_takeUpIndex = index;
    _G_U->setTakeUpProp(m_id, m_isTakeUp);
    _G_U->setTakeUpGunIndex(m_id, index);
    notify();
}
void Prop::takeDown()
{
    m_isTakeUp = false;
    m_takeUpIndex = 0;
    _G_U->setTakeUpProp(m_id, m_isTakeUp);
    _G_U->setTakeUpPropIndex(m_id, 0);
    notify();
}
int Prop::getTakeUpIndex()
{
    return m_takeUpIndex;
}
bool Prop::isTakeUp()
{
    return m_isTakeUp;
}
bool Prop::isUnlock()
{
    return m_isUnlock;
}
bool Prop::unlockProp()
{
    int userGold = _G_U->getUserGold();
    if (userGold < m_unlockGold)
    {
        return false;
    }
    userGold -= m_unlockGold;
    _G_U->setUserGold(userGold);
        
    m_isUnlock = true;
    _G_U->unlockProp(m_id);
    
    return true;
}
int Prop::getNum()
{
    return m_num;
}
//--- prop state ---
void Prop::setPropPoint(cocos2d::Vec2 point)
{
    m_point = point;
}
Vec2 Prop::getPropPoint()
{
    return m_point;
}
bool Prop::isCanArrve()
{
    float arrveLine = _G_M_M->enemy_start_buttomPoint.y + _G_M_M->enemy_start_upline;
    return m_point.y < arrveLine ? true : false;
}
void Prop::arrveCall()
{
    setStateArrve();
    Human::getInstance()->throwProp(this);
}
void Prop::throwCall()
{
    log("throw call");
    setStateReadyToHurt();
}
void Prop::setStateMoveing()
{
    m_state = p_moveing;
}
void Prop::setStateMoveEnd()
{
    m_state = p_moveEnd;
}
void Prop::setStateArrve()
{
    m_state = p_arrve;
}
void Prop::setStateThrowing()
{
    m_state = p_throw;
}
void Prop::setStateReadyToHurt()
{
    m_state = p_readyToHurt;
}
void Prop::setStateDie()
{
    m_state = p_die;
}
void Prop::setStateCanDelete()
{
    m_state = p_canDelete;
}
bool Prop::isMoveing()
{
    return m_state == p_moveing;
}
bool Prop::isMoveEnd()
{
    return m_state == p_moveEnd;
}
bool Prop::isArrve()
{
    return m_state == p_arrve;
}
bool Prop::isThrowing()
{
    return m_state == p_throw;
}
bool Prop::isReadyToHurt()
{
    return m_state == p_readyToHurt;
}
bool Prop::isDie()
{
    return m_state == p_die;
}
bool Prop::isCanDelete()
{
    return m_state == p_canDelete;
}

//--- get function ----
string Prop::getId()
{
    return m_id;
}
string Prop::getItemName()
{
    return m_itemName;
}
string Prop::getModelId()
{
    return m_modelId;
}
float Prop::getEffectArea()
{
    return m_effectArea;
}
float Prop::getDamage()
{
    return m_damage;
}
float Prop::getPercentageDamage()
{
    return m_percentageDamage;
}
vector<string> Prop::getBuffId()
{
    return m_buffIds;
}
string Prop::getUnlockMisstion()
{
    return m_unlockMission;
}
int Prop::getUnlockGold()
{
    return m_unlockGold;
}
int Prop::getPropPrice()
{
    return m_itemPrice;
}
string Prop::getItemDestription()
{
    return m_itemDestription;
}