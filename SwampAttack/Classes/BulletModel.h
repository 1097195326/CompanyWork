//
//  BulletModel.h
//  SwampAttack
//
//  Created by oceantech02 on 15/7/22.
//
//

#ifndef __SwampAttack__BulletModel__
#define __SwampAttack__BulletModel__

#include "BaseCode.h"
#include "json/json.h"

using namespace std;

class BulletModel {
private:
    string  m_id;
    string  m_modelId;
    std::vector<string> m_buffIds;
    string  m_explode;
    int     m_flyType;
    int     m_weaponType;
    string  m_description;
    
public:
    BulletModel(Json::Value data);
    ~BulletModel();
    
    string  getId();
    string  getModelId();
    std::vector<string> getBuffVector();
    string  getExplode();
    int     getFlyType();
    int     getWeaponType();
    string  getDescription();
    
};

#endif /* defined(__SwampAttack__BulletModel__) */
