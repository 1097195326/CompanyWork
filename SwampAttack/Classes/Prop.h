//
//  Prop.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/30.
//
//

#ifndef __SwampAttack__Prop__
#define __SwampAttack__Prop__


#include "GameObject.h"
#include "json/json.h"
#include "BaseCode.h"

using namespace std;

class Prop {
private:
    bool        m_isUnlock;
    int         m_num;
    
public:
    Prop(Json::Value value);
    ~Prop();
public:
    bool    isUnlock();
    int     getNum();
    
private:
    
    string      m_id;           //
    string      m_itemName;         //
    string      m_modelId;      //
    float       m_effectArea;   //
    float       m_damage;       //
    float       m_percentageDamage;//
    std::vector<string>  m_buffIds;
    int         m_itemPrice;
    string      m_unlockMission;
    int         m_unlockGold;
    string      m_itemDestription;
public:
    string      getId();
    string      getItemName();
    string      getModelId();
    float       getEffectArea();
    float       getDamage();
    float       getPercentageDamage();
    vector<string> getBuffId();
    string      getUnlockMisstion();
    int         getUnlockGold();
    string      getItemDestription();
    int         getPropPrice();
    
};

#endif /* defined(__SwampAttack__Prop__) */
