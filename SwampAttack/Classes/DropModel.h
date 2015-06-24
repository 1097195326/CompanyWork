//
//  DropModel.h
//  SwampAttack
//
//  Created by oceantech02 on 15/6/24.
//
//

#ifndef __SwampAttack__DropModel__
#define __SwampAttack__DropModel__

#include "BaseCode.h"
#include "json/json.h"
using namespace std;

struct DropData
{
    string  id = "";
    int     type = 0;
};
class DropModel {
private:
    string  m_id;
    std::map<string,int>    m_itemData;
    std::map<string,int>    m_moneyData;
    float   m_random;
public:
    
    DropData  getDropData();
    
    DropModel(Json::Value data);
    ~DropModel();
    
};

#endif /* defined(__SwampAttack__DropModel__) */
