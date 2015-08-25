//
//  BulletModel.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/7/22.
//
//

#include "BulletModel.h"


BulletModel::BulletModel(Json::Value data):
m_isHaveExplode(false)
{
    m_id = data["BulletId"].asString();
    m_modelId = data["ModelId"].asString();
    m_buffIds.reserve(4);
    Json::Value buffIds = data["BuffId"];
    if (buffIds.size() > 0) {
        for (int i = 0; i< buffIds.size(); ++i)
        {
            m_buffIds.push_back(buffIds[i].asString());
        }
    }
    m_explode = data["explode"].asString();
    if (m_explode.size() > 1)
    {
        m_isHaveExplode = true;
    }
    m_flyType = atoi(data["fly"].asString().c_str());
    m_acEffect = atoi(data["Effect"].asString().c_str());
    m_weaponType = atoi(data["WeaponType"].asString().c_str());
    m_description = data["ItemDescription"].asString();
}
BulletModel::~BulletModel()
{
    
}

string BulletModel::getId()
{
    return m_id;
}
string BulletModel::getModelId()
{
    return m_modelId;
}
std::vector<string> BulletModel::getBuffVector()
{
    return m_buffIds;
}
string BulletModel::getExplode()
{
    return m_explode;
}
int BulletModel::getFlyType()
{
    return m_flyType;
}
int BulletModel::getEffect()
{
    return m_acEffect;
}
int BulletModel::getWeaponType()
{
    return m_weaponType;
}
string BulletModel::getDescription()
{
    return m_description;
}

bool BulletModel::isHaveExplode()
{
    return m_isHaveExplode;
}