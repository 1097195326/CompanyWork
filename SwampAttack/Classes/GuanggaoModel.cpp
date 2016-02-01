//
//  GuanggaoModel.cpp
//  SwampAttack
//
//  Created by oceantech02 on 16/1/12.
//
//

#include "GuanggaoModel.hpp"
#include "GameUser.h"


GuanggaoModel::GuanggaoModel(Json::Value data):
m_isReady(false)
{
    m_id = data["AdvertisementId"].asString() ;
    m_time = atoi(data["Time"].asString().c_str());
    m_time *= 60;
    m_money = atoi(data["Money"].asString().c_str());
    
}


string GuanggaoModel::getId()
{
    return m_id;
}
int GuanggaoModel::getTime()
{
    return m_time;
}
int GuanggaoModel::getMoney()
{
    return m_money;
}
void GuanggaoModel::addMoney()
{
    int gold = _G_U->getUserGold();
    _G_U->setUserGold(gold + m_money);
}
bool GuanggaoModel::isReady()
{
    return m_isReady;
}
void GuanggaoModel::setReady(bool isReady)
{
    m_isReady = isReady;
}