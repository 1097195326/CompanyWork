//
//  GuanggaoModel.hpp
//  SwampAttack
//
//  Created by oceantech02 on 16/1/12.
//
//

#ifndef GuanggaoModel_hpp
#define GuanggaoModel_hpp

#include "json/json.h"

using std::string;

class GuanggaoModel
{
private:
    string      m_id;
    int         m_time;
    int         m_money;
    bool        m_isReady;
    
    
public:
    GuanggaoModel(Json::Value data);
    
    string  getId();
    int     getTime();
    int     getMoney();
    
    bool    isReady();
    void    setReady(bool isReady);
    
    void    addMoney();
};
#endif /* GuanggaoModel_hpp */
