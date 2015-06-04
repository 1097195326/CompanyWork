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
#include "GameObject.h"
class ShopPropIcon;

class PropManager : public GameObject {
private:
    std::map<string,Prop *> m_propData;
    std::map<int,std::string> m_hashHead;
    
    std::map<string,Prop *> m_takeUpPropData;
    std::list<Prop *> m_usingPropDta;
    
    std::vector<ShopPropIcon *>   m_propIcons;
    
public:
    //---
    Prop *  addUsingProp(string propId);
    //---
    Prop *   getPropByIndex(int index);
    int     getPropNum();
    //---
    int     getTakeUpPropNum();
    Prop *  getTakeUpPropByIndex(int index);
    int     getTakeUpPropIndexByName(string name);
    std::map<string,Prop *> getTakeUpProp();
    
    void    takeUpProp(string propId);
    void    takeDownProp(string propId);
    
    //---
    void    setShopView(Sprite * shopScene);
    void    setFightView();
    
public:
    static PropManager * getInstance();
    PropManager();
    ~PropManager();
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__PropManager__) */
