//
//  ConfigManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/3.
//
//

#include "ConfigManager.h"


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
Json::Value ConfigManager::getConfigByName(const std::string &cofName)
{
    if (m_dataMap[cofName]) {
        return m_dataMap[cofName]->getJsonData();
    }
    GCCsvHelper * csvHelper = new GCCsvHelper(cofName);
    return csvHelper->getJsonData();
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