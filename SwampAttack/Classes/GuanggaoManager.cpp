//
//  GuanggaoManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 16/1/12.
//
//

#include "GuanggaoManager.hpp"
#include "ConfigManager.h"

using std::string;

GuanggaoManager::GuanggaoManager()
{
    GCCsvHelper * propHelper = _C_M->getCsvHelperByName("guanggao");
    m_hashHead = propHelper->getHashHead();
    Json::Value data = propHelper->getJsonData();
    
    std::map<int,std::string>::iterator iter;
    for (iter = m_hashHead.begin(); iter != m_hashHead.end(); ++iter) {
        string dataId = iter->second;
        GuanggaoModel * model = new GuanggaoModel(data[dataId]);
        m_guanggaoData[dataId] = model;
    }
}
GuanggaoManager::~GuanggaoManager()
{
    
}
GuanggaoManager * GuanggaoManager::getIntantse()
{
    static GuanggaoManager manager;
    return &manager;
}

GuanggaoModel * GuanggaoManager::getGuangggaoModelByIndex(int index)
{
    string id = m_hashHead[index];
    return m_guanggaoData[id];
}