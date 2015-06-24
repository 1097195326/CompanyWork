//
//  DropManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/24.
//
//

#include "DropManager.h"
#include "ConfigManager.h"

#include "MoneyManager.h"
#include "PropManager.h"


DropManager::DropManager()
{
    GCCsvHelper * propHelper = _C_M->getCsvHelperByName("dropTable");
    m_hashHead = propHelper->getHashHead();
    Json::Value data = propHelper->getJsonData();
    
    std::map<int,std::string>::iterator iter;
    for (iter = m_hashHead.begin(); iter != m_hashHead.end(); ++iter) {
        string propId = iter->second;
        DropModel * drop = new DropModel(data[propId]);
        m_dropData[propId] = drop;
    }
}
DropManager::~DropManager()
{
    
}
DropManager * DropManager::getInstance()
{
    static DropManager manger;
    return &manger;
}
void DropManager::dropObject(string objId,Vec2 point)
{
    DropModel * model = m_dropData[objId];
    DropData dropData = model->getDropData();
    switch (dropData.type)
    {
        case 1:
        {
            MoneyManager::getInstance()->dropMoney(dropData.id,point);
        }
            break;
        case 2:
        {
            PropManager::getInstance()->dropProp(dropData.id,point);
        }
            break;
    }
}