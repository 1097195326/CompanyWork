//
//  ConfigManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/3.
//
//

#include "ConfigManager.h"

#include "GameConfig.h"


ConfigManager::ConfigManager()
{
    
}
ConfigManager::~ConfigManager()
{
    std::map<std::string, GCCsvHelper * >::iterator itr;
    for (itr = m_dataMap.begin(); itr != m_dataMap.end(); itr++) {
        GCCsvHelper * csvHelper = itr->second;
        delete csvHelper;
    }
    m_dataMap.clear();
}
ConfigManager * ConfigManager::getInstance()
{
    static ConfigManager configManger;
    return &configManger;
}
void ConfigManager::addConfigData(std::string confName, GCCsvHelper *csvHelper)
{
    m_dataMap[confName] = csvHelper;
}
GCCsvHelper * ConfigManager::getCsvHelperByName(const std::string &cofName)
{
//    log("get cofName:%s",cofName.c_str());
    if (m_dataMap.size() > 0 && m_dataMap[cofName]) {
        return m_dataMap[cofName];
    }
    GCCsvHelper * csvHelper = new GCCsvHelper(cofName);
    return csvHelper;
}
Json::Value ConfigManager::getConfigByName(const std::string &cofName)
{
    GCCsvHelper * csvHelper = getCsvHelperByName(cofName);
    return csvHelper->getJsonData();
}
int ConfigManager::getConfigDataNumByName(const std::string &cofName)
{
    GCCsvHelper * csvHelper = getCsvHelperByName(cofName);
    return csvHelper->getRowLength();
}
Json::Value ConfigManager::getDataByTag(const std::string &cofName, const std::string &tag)
{
    Json::Value root = getConfigByName(cofName);
    return root[tag];
}
Json::Value ConfigManager::getDataByName(const std::string &cofName, const std::string &tag, const std::string &name)
{
    Json::Value root = getConfigByName(cofName);
    Json::Value line = root[tag];
    return line[name];
}
Json::Value ConfigManager::getDataByNameFromData(const std::string &name, Json::Value &data)
{
    return data[name];
}
std::string ConfigManager::getTranslateById(std::string nameId)
{
    Json::Value data = getDataByName("translate", nameId, GameLanguage);
    return data.asString();
}