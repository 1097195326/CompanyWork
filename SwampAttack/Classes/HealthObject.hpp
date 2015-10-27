//
//  HealthObject.hpp
//  SwampAttack
//
//  Created by oceantech02 on 15/10/27.
//
//

#ifndef HealthObject_hpp
#define HealthObject_hpp

#include "json/json.h"
#include "BaseCode.h"

using namespace std;

class HealthObject {
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
    HealthObject(std::string id);
    ~HealthObject();
};

#endif /* HealthObject_hpp */
