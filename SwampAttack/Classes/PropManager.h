//
//  PropManager.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/30.
//
//

#ifndef __SwampAttack__PropManager__
#define __SwampAttack__PropManager__

#include "Prop.h"
class ShopPropIcon;

class PropManager {
private:
    std::map<string,Prop *> m_propData;
    std::map<int,std::string> m_hashHead;
    
    
    std::map<string,Prop *> m_takeUpPropData;
    std::vector<ShopPropIcon *>   m_propIcons;
    
public:
    Prop *   getPropByIndex(int index);
    int     getPropNum();
    
    int     getTakeUpPropNum();
    Prop *  getTakeUpPropByIndex(int index);
    int     getTakeUpPropIndexByName(string name);
    void    takeUpProp(string propId);
    void    takeDownProp(string propId);
    
    
    void    setShopView(Sprite * shopScene);
    
public:
    static PropManager * getInstance();
    PropManager();
    ~PropManager();
};

#endif /* defined(__SwampAttack__PropManager__) */
