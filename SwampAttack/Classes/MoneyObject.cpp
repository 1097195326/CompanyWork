//
//  MoneyObject.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/18.
//
//

#include "MoneyObject.h"
#include "ConfigManager.h"


MoneyObject::MoneyObject(std::string id)
{
    GCCsvHelper * specialHelper = _C_M->getCsvHelperByName("moneyTable");
    Json::Value data = specialHelper->getJsonData();
    Json::Value d = data[id];
//    log("money object:%s",d.toStyledString().c_str());
    m_id        = d["ID"].asString();
    m_name      = d["IDName"].asString();
    m_modelId   = d["ModelID"].asString();
    m_effect    = atoi(d["Effec"].asString().c_str());
    m_description= d["MoneyDescription"].asString();
    m_type      = atoi(d["type"].asString().c_str());
    
}
MoneyObject::~MoneyObject()
{
    
}

// get function

string MoneyObject::getId()
{
    return m_id;
}
string MoneyObject::getName()
{
    return m_name;
}
string MoneyObject::getModelId()
{
    return m_modelId;
}
int MoneyObject::getEffect()
{
    return m_effect;
}
string MoneyObject::getDescription()
{
    return m_description;
}
int MoneyObject::getType()
{
    return m_type;
}