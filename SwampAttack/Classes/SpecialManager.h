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
class SpecialObject;

using namespace std;

class SpecialManager {
private:
    std::map<int,MoneyObject *> m_moneyData;
    std::map<int,ExpendObject *> m_expendData;
    
    std::map<string,SpecialObject *> m_specialData;
    
    std::map<int,std::string> m_hashHead;
    
    
    SpecialManager();
    ~SpecialManager();
    
public:
    static SpecialManager * getInstance();
    
    SpecialObject * getSpecialObjectByIndex(int index);
    MoneyObject * getMoneyObjectByIndex(int index);
    ExpendObject * getExpendObjectByIndex(int index);
    
    void    addMoneyObjec(MoneyObject * object);
    void    addExpendObject(ExpendObject * object);
    
};

#endif /* defined(__SwampAttack__SpecialManager__) */
