//
//  SpecialObject.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/18.
//
//

#include "SpecialObject.h"

#include "GameUser.h"


SpecialObject::SpecialObject(Json::Value data):
m_moneyObject(NULL),
m_expendObject(NULL),
m_healthObject(NULL)
{
//    log("special :%s",data.toStyledString().c_str());
    m_id    =   data["ID"].asString();
    m_subId =   data["SubID"].asString();
    m_num   =   atoi(data["Number"].asString().c_str());
    m_price =   atoi(data["Price"].asString().c_str());
    m_type  =   atoi(data["Type"].asString().c_str());
    
    switch (m_type) {
        case 1:
        {
            m_moneyObject = new MoneyObject(m_subId);
        }
            break;
        case 2:
        {
            m_expendObject = new ExpendObject(m_subId);
        }
            break;
        case 3:
        {
            m_healthObject = new HealthObject(m_subId);
        }
            break;
    }
}
SpecialObject::~SpecialObject()
{
    if (m_moneyObject) {
        delete m_moneyObject;
    }
    if (m_expendObject) {
        delete m_expendObject;
    }
    if (m_healthObject) {
        delete m_healthObject;
    }
}
void SpecialObject::buyEnd()
{
    switch (m_type) {
        case 1:
        {
            int userGold = _G_U->getUserGold();
            int money = m_moneyObject->getEffect() * m_num;
            userGold += money;
            _G_U->setUserGold(userGold);
        }
            break;
        case 2:
        {
            int expendPropNum = _G_U->getExpendPropNum();
            int num = m_expendObject->getEffect() * m_num;
            expendPropNum += num;
            _G_U->setExpendPropNum(expendPropNum);
        }
            break;
        case 3:
        {
            _G_U->addHealthToFull();
        }
            break;
        default:
            break;
    }
}
///--- sub object funtion
string  SpecialObject::getName()
{
    string str;
    switch (m_type)
    {
        case 1:
        {
            str = m_moneyObject->getName();
        }
            break;
        case 2:
        {
            str = m_expendObject->getName();
        }
            break;
        case 3:
        {
            str = m_healthObject->getName();
        }
            break;
    }
    return str;
}
string  SpecialObject::getModelId()
{
    string str;
    switch (m_type)
    {
        case 1:
        {
            str = m_moneyObject->getModelId();
        }
            break;
        case 2:
        {
            str = m_expendObject->getModelId();
        }
            break;
        case 3:
        {
            str = m_healthObject->getModelId();
        }
            break;
    }
    return str;
}
int     SpecialObject::getEffect()
{
    int eff;
    switch (m_type)
    {
        case 1:
        {
            eff = m_moneyObject->getEffect();
        }
            break;
        case 2:
        {
            eff = m_expendObject->getEffect();
        }
            break;
        case 3:
        {
            eff = m_healthObject->getEffect();
        }
            break;
    }
    return eff;
}
string  SpecialObject::getDescription()
{
    string str;
    switch (m_type)
    {
        case 1:
        {
            str = m_moneyObject->getDescription();
        }
            break;
        case 2:
        {
            str = m_expendObject->getDescription();
        }
            break;
        case 3:
        {
            str = m_healthObject->getDescription();
        }
            break;
    }
    return str;
}
////--- get function
MoneyObject * SpecialObject::getMoneyObject()
{
    return m_moneyObject;
}
ExpendObject * SpecialObject::getExpendObject()
{
    return m_expendObject;
}
HealthObject * SpecialObject::getHealthObject()
{
    return m_healthObject;
}
string SpecialObject::getId()
{
    return m_id;
}
string SpecialObject::getSubId()
{
    return m_subId;
}
int SpecialObject::getNum()
{
    return m_num;
}
int SpecialObject::getPrice()
{
    return m_price;
}
int SpecialObject::getType()
{
    return m_type;
}