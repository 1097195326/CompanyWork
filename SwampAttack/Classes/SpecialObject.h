//
//  SpecialObject.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/18.
//
//

#ifndef __SwampAttack__SpecialObject__
#define __SwampAttack__SpecialObject__

#include "json/json.h"
#include "BaseCode.h"
#include "MoneyObject.h"
#include "ExpendObject.h"
#include "HealthObject.hpp"


using namespace std;


class SpecialObject  {
private:
    string      m_id;
    string      m_subId;
    int         m_num;
    int         m_price;
    int         m_translate;
    int         m_type;
    
    MoneyObject     *   m_moneyObject;
    ExpendObject    *   m_expendObject;
    HealthObject    *   m_healthObject;
public:
    void    buyEnd();
    MoneyObject     *   getMoneyObject();
    ExpendObject    *   getExpendObject();
    HealthObject    *   getHealthObject();
    
    string  getId();
    string  getSubId();
    int     getNum();
    int     getPrice();
    int     getType();

public:
    string  getName();
    string  getModelId();
    int     getEffect();
    string  getDescription();
public:
    SpecialObject(Json::Value data);
    ~SpecialObject();
};


#endif /* defined(__SwampAttack__SpecialObject__) */
