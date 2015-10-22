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
    std::list<Prop *> m_dropPropData;
    
    std::vector<ShopPropIcon *>   m_propIcons;
    std::string m_willTakeUpProp;
    int     m_dropCount;
public:
    //---
    Prop *  addUsingProp(string propId);
    //---
    Prop *   getPropByIndex(int index);
    Prop *   getPropById(string id);
    int     getPropNum();
    //---
    int     getTakeUpPropNum();
    Prop *  getTakeUpPropByIndex(int index);
    int     getTakeUpPropIndexByName(string name);
    std::map<string,Prop *> getTakeUpProp();
    
    void    takeUpProp(string propId);
    void    takeDownProp(string propId);
    
    void    setWillTakeUpProp(string propId);
    string  getWillTakeUpProp();
    void    takeUpWillProp();
    //---
    void    setShopView(Sprite * shopScene);
    void    setFightView();
    
    void    checkUnlock(Layer * layer);
    bool    dropProp(string id,Vec2 point);
    void    resetData();
public:
    static PropManager * getInstance();
    PropManager();
    ~PropManager();
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__PropManager__) */
