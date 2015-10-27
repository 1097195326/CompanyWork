//
//  HealthObject.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/10/27.
//
//

#include "HealthObject.hpp"
#include "ConfigManager.h"


HealthObject::HealthObject(std::string id)
{
    GCCsvHelper * specialHelper = _C_M->getCsvHelperByName("healthTable");
    Json::Value data = specialHelper->getJsonData();
    Json::Value d = data[id];
    //    log("expend object:%s",d.toStyledString().c_str());
    m_id        = d["ID"].asString();
    string name = d["IDName"].asString();
    m_name = _C_M->getTranslateById(name);
    m_modelId   = d["ModelID"].asString();
    m_effect    = atoi(d["Effec"].asString().c_str());
    string descri = d["Energy"].asString();
    m_description = _C_M->getTranslateById(descri);
    m_type      = atoi(d["type"].asString().c_str());
    
}
HealthObject::~HealthObject()
{
    
}

// get function

string HealthObject::getId()
{
    return m_id;
}
string HealthObject::getName()
{
    return m_name;
}
string HealthObject::getModelId()
{
    return m_modelId;
}
int HealthObject::getEffect()
{
    return m_effect;
}
string HealthObject::getDescription()
{
    return m_description;
}
int HealthObject::getType()
{
    return m_type;
}