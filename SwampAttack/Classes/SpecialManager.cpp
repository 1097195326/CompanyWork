//
//  SpecialManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/18.
//
//

#include "SpecialManager.h"
#include "ConfigManager.h"

#include "MoneyObject.h"
#include "ExpendObject.h"
#include "SpecialObject.h"


SpecialManager::SpecialManager()
{
    GCCsvHelper * specialHelper = _C_M->getCsvHelperByName("special");
    m_hashHead = specialHelper->getHashHead();
    Json::Value data = specialHelper->getJsonData();
    std::map<int,std::string>::iterator iter;
    for (iter = m_hashHead.begin(); iter != m_hashHead.end(); ++iter) {
        string specialId = iter->second;
        int specialType = atoi(data[specialId]["Type"].asString().c_str());
        SpecialObject * object = new SpecialObject(data[specialId]);
        m_specialData[specialId] = object;
        switch (specialType) {
            case 1:
                addMoneyObjec(object->getMoneyObject());
                break;
            case 2:
                addExpendObject(object->getExpendObject());
                break;
            default:
                break;
        }
    }
}
SpecialManager::~SpecialManager()
{
    
}
SpecialManager * SpecialManager::getInstance()
{
    static SpecialManager manager;
    return &manager;
}
void SpecialManager::addMoneyObjec(MoneyObject *object)
{
    int index = (int)m_moneyData.size();
    m_moneyData[index] = object;
}
void SpecialManager::addExpendObject(ExpendObject *object)
{
    int index = (int)m_expendData.size();
    m_expendData[index] = object;
}
SpecialObject * SpecialManager::getSpecialObjectByIndex(int index)
{
    string id = m_hashHead[index];
    return m_specialData[id];
}
SpecialObject * SpecialManager::getSpecialObjectById(std::string _id)
{
    if(_id == "")
    {
        return NULL;
    }
    return m_specialData[_id];
}
SpecialObject * SpecialManager::getSpecialObjectBySubId(std::string _id,int type)
{
    SpecialObject * specialObject = NULL;
    std::map<string,SpecialObject *>::iterator iter;
    for (iter = m_specialData.begin(); iter != m_specialData.end(); ++iter)
    {
        SpecialObject * object = iter->second;
        if (object->getType() == type && object->getSubId() == _id)
        {
            specialObject = object;
            break;
        }
    }
    return specialObject;
}
MoneyObject * SpecialManager::getMoneyObjectByIndex(int index)
{
    return m_moneyData[index];
}
ExpendObject * SpecialManager::getExpendObjectByIndex(int index)
{
    return m_expendData[index];
}
std::map<int,MoneyObject *> SpecialManager::getMoneyData()
{
    return m_moneyData;
}
std::map<int,ExpendObject *> SpecialManager::getExpendData()
{
    return m_expendData;
}
int SpecialManager::getSpecialNum()
{
    return (int)m_specialData.size();
}