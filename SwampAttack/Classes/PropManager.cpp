//
//  PropManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/30.
//
//

#include "PropManager.h"
#include "ConfigManager.h"


PropManager::PropManager()
{
    GCCsvHelper * propHelper = _C_M->getCsvHelperByName("daoju");
    m_hashHead = propHelper->getHashHead();
    Json::Value data = propHelper->getJsonData();
    
    std::map<int,std::string>::iterator iter;
    for (iter = m_hashHead.begin(); iter != m_hashHead.end(); ++iter) {
        string propId = iter->second;
        m_propData[propId] = new Prop(data[propId]);
    }
    
}
PropManager::~PropManager()
{
    
}
PropManager * PropManager::getInstance()
{
    static PropManager manager;
    return &manager;
}
Prop * PropManager::getPropByIndex(int index)
{
    string propId = m_hashHead[index];
    return m_propData[propId];
}
int PropManager::getPropNum()
{
    return (int)m_propData.size();
}