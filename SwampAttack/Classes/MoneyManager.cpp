//
//  MoneyManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/24.
//
//

#include "MoneyManager.h"
#include "ConfigManager.h"


MoneyManager::MoneyManager()
{
    GCCsvHelper * propHelper = _C_M->getCsvHelperByName("moneyTable");
    m_hashHead = propHelper->getHashHead();
    Json::Value data = propHelper->getJsonData();
    
    std::map<int,std::string>::iterator iter;
    for (iter = m_hashHead.begin(); iter != m_hashHead.end(); ++iter) {
        string moneyId = iter->second;
        MoneyObject * obj = new MoneyObject(moneyId);
        m_moneyData[moneyId] = obj;
    }
}
MoneyManager::~MoneyManager()
{
    
}
MoneyManager * MoneyManager::getInstance()
{
    static MoneyManager manager;
    return &manager;
}
MoneyObject * MoneyManager::getMoneyObjectById(string id)
{
    return m_moneyData[id];
}
void MoneyManager::dropMoney(string id,Vec2 point)
{
    
}