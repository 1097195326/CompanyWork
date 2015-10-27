//
//  SpecialManager.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/18.
//
//

#ifndef __SwampAttack__SpecialManager__
#define __SwampAttack__SpecialManager__

#include "BaseCode.h"
class MoneyObject;
class ExpendObject;
class HealthObject;
#include "SpecialObject.h"

using namespace std;

class SpecialManager {
private:
    std::map<int,MoneyObject *> m_moneyData;
    std::map<int,ExpendObject *> m_expendData;
    std::map<int,HealthObject *> m_healthData;
    
    std::map<string,SpecialObject *> m_specialData;
    
    std::map<int,std::string> m_hashHead;
    
    
    SpecialManager();
    ~SpecialManager();
    
public:
    static SpecialManager * getInstance();
    
    SpecialObject * getSpecialObjectByIndex(int index);
    SpecialObject * getSpecialObjectById(std::string _id);
    SpecialObject * getSpecialObjectBySubId(std::string _id,int type);
    MoneyObject * getMoneyObjectByIndex(int index);
    ExpendObject * getExpendObjectByIndex(int index);
    HealthObject * getHealthObjectByIndex(int index);
    
    std::map<int,MoneyObject *> getMoneyData();
    std::map<int,ExpendObject *> getExpendData();
    std::map<int,HealthObject *> getHealthData();
    
    int     getSpecialNum();
    
    void    addMoneyObjec(MoneyObject * object);
    void    addExpendObject(ExpendObject * object);
    void    addHealthObject(HealthObject * object);
    
};

#endif /* defined(__SwampAttack__SpecialManager__) */
