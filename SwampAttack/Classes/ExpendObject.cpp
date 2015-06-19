//
//  ExpendObject.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/18.
//
//

#include "ExpendObject.h"
#include "ConfigManager.h"


ExpendObject::ExpendObject(std::string id)
{
    GCCsvHelper * specialHelper = _C_M->getCsvHelperByName("expendTable");
    Json::Value data = specialHelper->getJsonData();
    Json::Value d = data[id];
//    log("expend object:%s",d.toStyledString().c_str());
    m_id        = d["ID"].asString();
    string name = d["IDName"].asString();
    m_name = _C_M->getTranslateById(name);
    m_modelId   = d["ModelID"].asString();
    m_effect    = atoi(d["Effec"].asString().c_str());
    string descri = d["HpDescription"].asString();
    m_description = _C_M->getTranslateById(descri);
    m_type      = atoi(d["type"].asString().c_str());
    
}
ExpendObject::~ExpendObject()
{
    
}

// get function

string ExpendObject::getId()
{
    return m_id;
}
string ExpendObject::getName()
{
    return m_name;
}
string ExpendObject::getModelId()
{
    return m_modelId;
}
int ExpendObject::getEffect()
{
    return m_effect;
}
string ExpendObject::getDescription()
{
    return m_description;
}
int ExpendObject::getType()
{
    return m_type;
}