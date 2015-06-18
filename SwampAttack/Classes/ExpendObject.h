//
//  ExpendObject.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/18.
//
//

#ifndef __SwampAttack__ExpendObject__
#define __SwampAttack__ExpendObject__

#include "json/json.h"
#include "BaseCode.h"

using namespace std;

class ExpendObject {
private:
    string  m_id;
    string  m_name;
    string  m_modelId;
    int     m_effect;
    string  m_description;
    int     m_type;
public:
    string  getId();
    string  getName();
    string  getModelId();
    int     getEffect();
    string  getDescription();
    int     getType();
public:
    ExpendObject(std::string id);
    ~ExpendObject();
};

#endif /* defined(__SwampAttack__ExpendObject__) */
