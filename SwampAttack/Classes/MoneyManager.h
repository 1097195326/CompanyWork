//
//  MoneyManager.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/24.
//
//

#ifndef __SwampAttack__MoneyManager__
#define __SwampAttack__MoneyManager__

#include "MoneyObject.h"


class MoneyManager {
private:
    std::map<string,MoneyObject *>    m_moneyData;
    std::map<int,std::string> m_hashHead;
    
    
    MoneyManager();
    ~MoneyManager();
public:
    static MoneyManager * getInstance();
    MoneyObject * getMoneyObjectById(string id);
    void    dropMoney(string id,Vec2 point);
};

#endif /* defined(__SwampAttack__MoneyManager__) */
