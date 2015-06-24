//
//  DropModel.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/24.
//
//

#include "DropModel.h"

DropModel::DropModel(Json::Value data)
{
//    log("drop model:%s",data.toStyledString().c_str());
    
    m_id = data["Id"].asString();
    Json::Value itemData = data["ItemId"];
    for (int i = 0; i < itemData.size(); ++i)
    {
        string itemid = itemData[i]["itemid"].asString();
        int percent = atoi(itemData[i]["percent"].asString().c_str());
        m_itemData[itemid] = percent;
    }
    Json::Value moneyData = data["MoneyId"];
    for (int i = 0; i < moneyData.size(); ++i)
    {
        string moneyid = moneyData[i]["moneyid"].asString();
        int percent = atoi(moneyData[i]["percent"].asString().c_str());
        m_moneyData[moneyid] = percent;
    }
    m_random = atof(data["Random"].asString().c_str());
    
}
DropModel::~DropModel()
{
    
}
DropData DropModel::getDropData()
{
    DropData data;
    int rd = m_random;
//    int _r = random(1, 100);
//    log("1111:%d,%d",_r,rd);
    if(random(1, 100) <= rd)
    {
        
        std::map<string,int>::iterator iter;
        for (iter = m_itemData.begin(); iter != m_itemData.end(); ++iter)
        {
            int r = iter->second;
            if (random(1, rd) <= r)
            {
                data.id = iter->first;
                data.type = 2;
                break;
            }
            rd -= r;
        }
        for (iter = m_moneyData.begin(); iter != m_moneyData.end(); ++iter)
        {
            int r = iter->second;
            if (random(1, rd) <= r)
            {
                data.id = iter->first;
                data.type = 1;
                break;
            }
            rd -= r;
        }
    }
    return data;
}