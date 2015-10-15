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

#include "GameUser.h"


DropManager::DropManager():
m_dropNum(0)
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
//    log("drop obj %s",objId.c_str());
    bool res = false;
    DropModel * model = m_dropData[objId];
    DropData dropData = model->getDropData();
    if (!_G_U->isHaveXinshouYindao() && m_dropNum == 0)
    {
        dropData.id = "500001";
        dropData.type = 2;
    }
    switch (dropData.type)
    {
        case 1:
        {
            res = MoneyManager::getInstance()->dropMoney(dropData.id,point);
        }
            break;
        case 2:
        {
            res = PropManager::getInstance()->dropProp(dropData.id,point);
        }
            break;
    }
    
    if (res)
    {
        addDropNum();
    }
}
void DropManager::addDropNum()
{
    ++m_dropNum;
}
void DropManager::minusDropNum()
{
    --m_dropNum;
    m_dropNum = m_dropNum < 0 ? 0 : m_dropNum;
}
int DropManager::getDropNum()
{
    return m_dropNum;
}