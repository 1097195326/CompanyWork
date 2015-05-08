//
//  ConfigManager.h
//  SwampAttack
//
//  Created by oceantech02 on 15/4/3.
//
//

#ifndef __SwampAttack__ConfigManager__
#define __SwampAttack__ConfigManager__

#include "json/json.h"
#include <map>
#include "CCCsvHelper.h"

#define _C_M ConfigManager::getInstance()

class ConfigManager
{
private:
    std::map<std::string, GCCsvHelper *> m_dataMap;
private:
    ConfigManager();
    ~ConfigManager();
public:
    static ConfigManager * getInstance();
    void            addConfigData(std::string confName, GCCsvHelper * csvHelper);
    
    GCCsvHelper *   getCsvHelperByName(const std::string & cofName);
    Json::Value     getConfigByName(const std::string & cofName);
    int             getConfigDataNumByName(const std::string & cofName);
    Json::Value     getDataByTag(const std::string & cofName, const std::string & tag);
    Json::Value     getDataByName(const std::string & cofName,const std::string & tag, const std::string & name);
    Json::Value     getDataByNameFromData(const std::string & name, Json::Value & data);
    std::string     getTranslateById(std::string nameId);
    
    
};

#endif /* defined(__SwampAttack__ConfigManager__) */
