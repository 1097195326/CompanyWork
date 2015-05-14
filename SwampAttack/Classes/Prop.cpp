//
//  Prop.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/30.
//
//

#include "Prop.h"
#include "ConfigManager.h"
#include "GameUser.h"


Prop::Prop(Json::Value data):m_isUnlock(false),m_num(0)
{
    m_id = data["ItemId"].asString() ;
    string itemName = data["ItemName"].asString();
    m_itemName = _C_M->getTranslateById(itemName);
    m_modelId = data["ModelId"].asString();
    m_effectArea = atof(data["EffectArea"].asString().c_str());
    m_unlockMission = data["UnlockMission"].asString();
    m_unlockGold = atoi(data["UnlockGold"].asString().c_str());
    m_itemPrice = atoi(data["ItemPrice"].asString().c_str());
    m_damage =
    data["Damage"].asString() == "" ?
    0 : atof(data["Damage"].asString().c_str());
    m_percentageDamage =
    data["PercentageDamage"].asString() == "" ?
    0 : atof(data["PercentageDamage"].asString().c_str());
    
    m_buffIds.reserve(4);
    Json::Value buffIds = data["BuffId"];
    if (buffIds.size() > 0) {
        for (int i = 0; i< buffIds.size(); ++i)
        {
            m_buffIds.push_back(buffIds[i].asString());
        }
    }
    string itemDescription = data["ItemDescription"].asString();
    m_itemDestription = _C_M->getTranslateById(itemDescription);
    
    m_num = _G_U->getPropNum(m_id);
    m_isUnlock = _G_U->isUnlockProp(m_id);
    
}
Prop::~Prop()
{
    
}


bool Prop::isUnlock()
{
    return m_isUnlock;
}
int Prop::getNum()
{
    return m_num;
}

//--- get function ----
string Prop::getId()
{
    return m_id;
}
string Prop::getItemName()
{
    return m_itemName;
}
string Prop::getModelId()
{
    return m_modelId;
}
float Prop::getEffectArea()
{
    return m_effectArea;
}
float Prop::getDamage()
{
    return m_damage;
}
float Prop::getPercentageDamage()
{
    return m_percentageDamage;
}
vector<string> Prop::getBuffId()
{
    return m_buffIds;
}
string Prop::getUnlockMisstion()
{
    return m_unlockMission;
}
int Prop::getUnlockGold()
{
    return m_unlockGold;
}
int Prop::getPropPrice()
{
    return m_itemPrice;
}
string Prop::getItemDestription()
{
    return m_itemDestription;
}