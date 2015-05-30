//
//  GuanQiaManager.cpp
//  SwampAttack
//
//  Created by 张洪星 on 15/5/30.
//
//

#include "GuanQiaManager.h"

#include "ConfigManager.h"


GuanQiaManager::GuanQiaManager()
{
    GCCsvHelper * propHelper = _C_M->getCsvHelperByName("guanqia");
    m_hashHead = propHelper->getHashHead();
    Json::Value data = propHelper->getJsonData();
    
    std::map<int,std::string>::iterator iter;
    for (iter = m_hashHead.begin(); iter != m_hashHead.end(); ++iter) {
        string guanqiaId = iter->second;
        GuanqiaModel * guanqia = new GuanqiaModel(data[guanqiaId]);
        m_guanQiaData[guanqiaId] = guanqia;
        
    }
    
}
GuanQiaManager::~GuanQiaManager()
{
    
}
GuanQiaManager * GuanQiaManager::getInstance()
{
    static GuanQiaManager manager;
    return &manager;
}
GuanqiaModel * GuanQiaManager::getGuanqiaByIndex(int index)
{
    string guanqiaId = m_hashHead[index];
    return m_guanQiaData[guanqiaId];
}
GuanqiaModel * GuanQiaManager::getGuanqiaById(string guanqiaId)
{
    return m_guanQiaData[guanqiaId];
}
int GuanQiaManager::getGuanqiaNum()
{
    return (int)m_guanQiaData.size();
}
