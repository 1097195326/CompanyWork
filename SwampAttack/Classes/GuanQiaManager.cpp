//
//  GuanQiaManager.cpp
//  SwampAttack
//
//  Created by 张洪星 on 15/5/30.
//
//

#include "GuanQiaManager.h"

#include "ConfigManager.h"
#include "GameUser.h"


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
    
    m_currentSceneIndex = _G_U->getLastSceneIndex();
    m_currentGuanqiaIndex = _G_U->getLastGuanqiaIndex();
    
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
void GuanQiaManager::setCurrentGuanqiaId(string guanqiaId)
{
    m_currentGuanqiaId = guanqiaId;
}
GuanqiaModel * GuanQiaManager::getCurrentGuanqia()
{
    return m_guanQiaData[m_currentGuanqiaId];
}
void GuanQiaManager::setCurrentSceneIndex(int index)
{
    if (index > m_currentSceneIndex)
    {
        _G_U->setLastSceneIndex(index);
    }
    m_currentSceneIndex = index;
    
}
int GuanQiaManager::getCurrentSceneIndex()
{
    return m_currentSceneIndex;
}
void GuanQiaManager::setCurrentGuanqiaIndex(int index)
{
    if (index > m_currentGuanqiaIndex)
    {
        _G_U->setLastGuanqiaIndex(index);
    }
    m_currentGuanqiaIndex = index;
    
}
int GuanQiaManager::getCurrentGuanqiaIndex()
{
    return m_currentGuanqiaIndex;
}